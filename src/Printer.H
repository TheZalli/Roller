#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2000
/* You may wish to change _L_PAREN or _R_PAREN */
#define _L_PAREN '('
#define _R_PAREN ')'

class PrintAbsyn : public Visitor
{
 protected:
  int _n_, _i_;
  /* The following are simple heuristics for rendering terminals */
  /* You may wish to change them */
  void render(Char c);
  void render(String s);
void render(char *s);
  void indent(void);
  void backup(void);
 public:
  PrintAbsyn(void);
  ~PrintAbsyn(void);
  char *print(Visitable *v);

  void visitCmd(Cmd *p); /* abstract class */
  void visitExpCmd(ExpCmd *p);
  void visitStmtCmd(StmtCmd *p);
  void visitExp(Exp *p); /* abstract class */
  void visitEKeyW(EKeyW *p);
  void visitEAdd(EAdd *p);
  void visitESub(ESub *p);
  void visitEMul(EMul *p);
  void visitEDiv(EDiv *p);
  void visitEVal(EVal *p);
  void visitESeq(ESeq *p);
  void visitEDice(EDice *p);
  void visitESeqFilt(ESeqFilt *p);
  void visitECall(ECall *p);
  void visitListExp(ListExp *p);
  void visitNumeral(Numeral *p); /* abstract class */
  void visitIntNum(IntNum *p);
  void visitIntNegNum(IntNegNum *p);
  void visitVal(Val *p); /* abstract class */
  void visitValNum(ValNum *p);
  void visitValVar(ValVar *p);
  void visitValStr(ValStr *p);
  void visitExpSeq(ExpSeq *p); /* abstract class */
  void visitERange(ERange *p);
  void visitERStep(ERStep *p);
  void visitEVect(EVect *p);
  void visitExpD(ExpD *p); /* abstract class */
  void visitE1d6(E1d6 *p);
  void visitE1dN(E1dN *p);
  void visitENd6(ENd6 *p);
  void visitENdN(ENdN *p);
  void visitExpKW(ExpKW *p); /* abstract class */
  void visitEKCount(EKCount *p);
  void visitEKSum(EKSum *p);
  void visitEKRepeat(EKRepeat *p);
  void visitEKMean(EKMean *p);
  void visitEKAcc(EKAcc *p);
  void visitPred(Pred *p); /* abstract class */
  void visitPredBranch(PredBranch *p);
  void visitPredAnd(PredAnd *p);
  void visitPredOr(PredOr *p);
  void visitPredXOr(PredXOr *p);
  void visitPredEQ(PredEQ *p);
  void visitPredNEQ(PredNEQ *p);
  void visitPredGT(PredGT *p);
  void visitPredLT(PredLT *p);
  void visitPredGTEq(PredGTEq *p);
  void visitPredLTEq(PredLTEq *p);
  void visitPredIsStr(PredIsStr *p);
  void visitPredInd(PredInd *p);
  void visitPredRange(PredRange *p);
  void visitPredRStep(PredRStep *p);
  void visitStmt(Stmt *p); /* abstract class */
  void visitSVarAs(SVarAs *p);
  void visitSFDef(SFDef *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
  void visitVarIdent(String s);
 protected:
  void inline bufAppend(const char *s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }

  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }

  void inline bufAppend(String str)
  {
    const char *s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }

  void inline resizeBuffer(void)
  {
    char *temp = (char *) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;
};



class ShowAbsyn : public Visitor
{
 public:
  ShowAbsyn(void);
  ~ShowAbsyn(void);
  char *show(Visitable *v);

  void visitCmd(Cmd *p); /* abstract class */
  void visitExpCmd(ExpCmd *p);
  void visitStmtCmd(StmtCmd *p);
  void visitExp(Exp *p); /* abstract class */
  void visitEKeyW(EKeyW *p);
  void visitEAdd(EAdd *p);
  void visitESub(ESub *p);
  void visitEMul(EMul *p);
  void visitEDiv(EDiv *p);
  void visitEVal(EVal *p);
  void visitESeq(ESeq *p);
  void visitEDice(EDice *p);
  void visitESeqFilt(ESeqFilt *p);
  void visitECall(ECall *p);
  void visitListExp(ListExp *p);
  void visitNumeral(Numeral *p); /* abstract class */
  void visitIntNum(IntNum *p);
  void visitIntNegNum(IntNegNum *p);
  void visitVal(Val *p); /* abstract class */
  void visitValNum(ValNum *p);
  void visitValVar(ValVar *p);
  void visitValStr(ValStr *p);
  void visitExpSeq(ExpSeq *p); /* abstract class */
  void visitERange(ERange *p);
  void visitERStep(ERStep *p);
  void visitEVect(EVect *p);
  void visitExpD(ExpD *p); /* abstract class */
  void visitE1d6(E1d6 *p);
  void visitE1dN(E1dN *p);
  void visitENd6(ENd6 *p);
  void visitENdN(ENdN *p);
  void visitExpKW(ExpKW *p); /* abstract class */
  void visitEKCount(EKCount *p);
  void visitEKSum(EKSum *p);
  void visitEKRepeat(EKRepeat *p);
  void visitEKMean(EKMean *p);
  void visitEKAcc(EKAcc *p);
  void visitPred(Pred *p); /* abstract class */
  void visitPredBranch(PredBranch *p);
  void visitPredAnd(PredAnd *p);
  void visitPredOr(PredOr *p);
  void visitPredXOr(PredXOr *p);
  void visitPredEQ(PredEQ *p);
  void visitPredNEQ(PredNEQ *p);
  void visitPredGT(PredGT *p);
  void visitPredLT(PredLT *p);
  void visitPredGTEq(PredGTEq *p);
  void visitPredLTEq(PredLTEq *p);
  void visitPredIsStr(PredIsStr *p);
  void visitPredInd(PredInd *p);
  void visitPredRange(PredRange *p);
  void visitPredRStep(PredRStep *p);
  void visitStmt(Stmt *p); /* abstract class */
  void visitSVarAs(SVarAs *p);
  void visitSFDef(SFDef *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
  void visitVarIdent(String s);
 protected:
  void inline bufAppend(const char *s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }

  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }

  void inline bufAppend(String str)
  {
    const char *s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }

  void inline resizeBuffer(void)
  {
    char *temp = (char *) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;
};




#endif

