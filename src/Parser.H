#ifndef PARSER_HEADER_FILE
#define PARSER_HEADER_FILE

#include<vector>
#include<string>


class Cmd;
class Exp;
class ListExp;
class Numeral;
class Val;
class Range;
class ExpD;
class ExpKW;
class Pred;
class ListPred;
class Stmt;

typedef union
{
  int int_;
  char char_;
  double double_;
  char* string_;
  Cmd* cmd_;
  Exp* exp_;
  ListExp* listexp_;
  Numeral* numeral_;
  Val* val_;
  Range* range_;
  ExpD* expd_;
  ExpKW* expkw_;
  Pred* pred_;
  ListPred* listpred_;
  Stmt* stmt_;
} YYSTYPE;

Cmd* pCmd(FILE *inp);
Cmd* pCmd(const char *str);
Exp* pExp(FILE *inp);
Exp* pExp(const char *str);
ListExp* pListExp(FILE *inp);
ListExp* pListExp(const char *str);
Numeral* pNumeral(FILE *inp);
Numeral* pNumeral(const char *str);
Val* pVal(FILE *inp);
Val* pVal(const char *str);
Range* pRange(FILE *inp);
Range* pRange(const char *str);
ExpD* pExpD(FILE *inp);
ExpD* pExpD(const char *str);
ExpKW* pExpKW(FILE *inp);
ExpKW* pExpKW(const char *str);
Pred* pPred(FILE *inp);
Pred* pPred(const char *str);
ListPred* pListPred(FILE *inp);
ListPred* pListPred(const char *str);
Stmt* pStmt(FILE *inp);
Stmt* pStmt(const char *str);



#define _ERROR_ 258
#define _SYMB_0 259
#define _SYMB_1 260
#define _SYMB_2 261
#define _SYMB_3 262
#define _SYMB_4 263
#define _SYMB_5 264
#define _SYMB_6 265
#define _SYMB_7 266
#define _SYMB_8 267
#define _SYMB_9 268
#define _SYMB_10 269
#define _SYMB_11 270
#define _SYMB_12 271
#define _SYMB_13 272
#define _SYMB_14 273
#define _SYMB_15 274
#define _SYMB_16 275
#define _SYMB_17 276
#define _SYMB_18 277
#define _SYMB_19 278
#define _SYMB_20 279
#define _SYMB_21 280
#define _SYMB_22 281
#define _SYMB_23 282
#define _SYMB_24 283
#define _SYMB_25 284
#define _SYMB_26 285
#define _SYMB_27 286
#define _SYMB_28 287
#define _SYMB_29 288
#define _SYMB_30 289
#define _SYMB_31 290
#define _SYMB_32 291
#define _SYMB_33 292
#define _SYMB_34 293
#define _SYMB_35 294
#define _SYMB_36 295
#define _SYMB_37 296
#define _SYMB_38 297
#define _SYMB_39 298
#define _STRING_ 299
#define _INTEGER_ 300
#define _DOUBLE_ 301

extern YYSTYPE yylval;

#endif
