#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

/* トークンの最大長 */
#define MAXOP		100

/* トークンのタイプ */
#define NUMBER		'0'
#define IDENTIFIER	'i'
#define ERROR		'e'
#define VAR_REF		'v'
#define ASSIGN		'a'

int getop(char []);
void push(double);
double pop(void);
double top(void);
void call_func(const char *name);
int reference(char letter, double *out);
double assign(char letter, double value);

/* 数学関数のシグネチャー */
typedef double (* D)(double);
typedef double (* DD)(double,double);
typedef double (* DI)(double,int);
typedef double (* DDp)(double,double*);
typedef double (* DIp)(double,int*);

/* シグネチャのタイプ。十の位はアリティー */
typedef enum {
	S_D   = 10,
	S_DD  = 21,
	S_DI  = 22,
	S_DDp = 13,
	S_DIp = 14
} signature_t;

/* 数学関数エントリー */
struct FUNC {
	char *name;
	signature_t signature;
	union {
		/* キャストのない、リテラル初期化の為に */
		void *p;

		D d;
		DD dd;
		DI di;
		DDp ddp;
		DIp dip;
	} pt;
};

#include <limits.h>

double var[2 << CHAR_BIT] = { 0.0 };
int var_assigned[2 << CHAR_BIT] = { 0 };

main()
{
	int type;
	double op2;
	double tmp, tmp2;
	extern int sp;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			push((int) pop() % (int) op2);
			break;
		case '\n':
			printf("\t\t%.8g\n", assign('$', pop()));
			break;
		case IDENTIFIER:
			if (s[1] == '\0') {
				switch (s[0]) {
				case 'p':
					tmp = pop();
					printf("\t%.8g\n", tmp);
					push(tmp);
					break;
				case 'c':
					tmp = pop();
					push(tmp); push(tmp);
					break;
				case 'x':
					tmp = pop(); tmp2 = pop();
					push(tmp); push(tmp2);
					break;
				case 'e':
					while (sp != 0)
						pop();
					break;
				default:
					goto FunctionCall;
				}
				goto End;
			}
		FunctionCall:
			call_func(s);
			break;
		case VAR_REF:
			if (reference(s[1], &tmp) == 0) {
				push(tmp);
			} else {
				printf("undefined variable %c\n", s[1]);
				goto Error;
			}
			break;
		case ASSIGN:
			assign(s[1], top());
			break;
		case ERROR:
		Error:
		{
			int c;

			//	while ((c = getch()) != '\n' || c != EOF)
			//	  ;
		}
		break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	End:;
	}
	return 0;
}

int arity(signature_t s)
{
	return s/10;
}

void call_func(const char *name)
{
	static struct FUNC func[] = {
		{"sin",		S_D,		sin	},
		{"cos",		S_D,		cos	},
		{"tan",		S_D,		tan	},
		{"asin",	S_D,		asin	},
		{"acos",	S_D,		acos	},
		{"atan",	S_D,		atan	},
		{"atan2",	S_DD,		atan2	},
		{"sinh",	S_D,		sinh	},
		{"cosh",	S_D,		cosh	},
		{"tanh",	S_D,		tanh	},
		{"exp",		S_D,		exp	},
		{"log",		S_D,		log	},
		{"log10",	S_D,		log10	},
		{"pow",		S_DD,		pow	},
		{"sqrt",	S_D,		sqrt	},
		{"ceil",	S_D,		ceil	},
		{"floor",	S_D,		floor	},
		{"fabs",	S_D,		fabs	},
		{"ldexp",	S_DI,		ldexp	},
		{"frexp",	S_DIp,		frexp	},
		{"modf",	S_DDp,		modf	},
		{"fmod",	S_DD,		fmod	},
		{NULL,		0,		NULL	}
	};
	int i;
	double t, u;
	double ret;

	for (i = 0; func[i].name != NULL; ++i) {
		if (strcmp(func[i].name, name) == 0) {
			switch (func[i].signature) {
			case S_D:
				t = pop();
				push( ret = func[i].pt.d(t) );
				break;
			case S_DD:
				t = pop();
				u = pop();
				push( ret = func[i].pt.dd(u,t) );
				break;
			case S_DI:
				t = pop();
				u = pop();
				push( ret = func[i].pt.di(u,t) );
				break;
			case S_DDp:
				t = pop();
				push( ret = func[i].pt.ddp(t,&u) );
				push(u);
				break;
			case S_DIp:
			{
				int n;

				t = pop();
				push( ret = func[i].pt.dip(t,&n) );
				push(n);
			}
			break;
			default:
				printf("error: unknown signature\n");
				break;
			}
			if ((ret == HUGE_VAL || ret == -HUGE_VAL)
			    && errno == ERANGE) {
				printf("error: range error\n");
			}
			return;
		}
	}
	printf("error: unknown function %s\n", name);
	return;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

double top(void)
{
	if (sp > 0)
		return val[sp-1];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/*
 * 標準入力より次のトークンを得る。
 * s にはトークンが入り、返り値はトークンが演算子ならば
 * その文字、数字ならば '0'。
 */
int getop(char s[])
{
	int i, c;

	/* 空白を読みとばし、*/
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (c == EOF)
		return EOF;
	/* 最初の文字が s[0] と c に入った。 */
	if (!isdigit(c) && c != '.' && c != '-') {
		/* わからない記号か、識別子の先頭 */
		if (isalpha(c)) {
			for (i = 1; isalnum(c = getch()); ++i) 
				s[i] = c;
			if (c != EOF)
				ungetch(c);
			s[i] = '\0';
			return IDENTIFIER;
		} else if (c == '=') {
			/* 次の文字がアルファベットだったら ASSIGN */
			/* さもなくば、文法エラー */
			if (isalpha(c = getch())) {
				s[1] = c;
				s[2] = '\0';
				return ASSIGN;
			} else { /* EOF でも */
				printf("error: variable letter expected after =\n");
				return ERROR;
			}
		} else if (c == '$') {
			if (isalpha(c = getch()) || c == '$') {
				s[1] = c;
				s[2] = '\0';
				return VAR_REF;
			} else { /* EOF でも */
				printf("error: variable name expected after $\n");
				return ERROR;
			}
		} else if (c == '+' || c == '*' || c == '/' || c == '%' || c == '\n') {
			return c;
		} else {
			printf("error: parse error on '%c'\n", c);
			return ERROR;
		}
	}
	i = 0;
	if (isdigit(c) || c == '-')
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (s[0] == '-' && s[1] == '\0') {
		ungetch(c);
		return '-';
	}
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp> 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/*
 * 変数を参照する。変数が定義されていれば 0 を返し、
 * *out にその値を設定する。
 */
#include <assert.h>

int reference(char letter, double *out)
{
	if (var_assigned[letter]) {
		*out = var[letter];
		return 0;
	} else {
		return -1;
	}
}

double assign(char letter, double value)
{
	var[letter] = value;
	var_assigned[letter] = 1;

	return value;
}

