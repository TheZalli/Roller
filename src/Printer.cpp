/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2


//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppend(' ');
     bufAppend(c);
     bufAppend(' ');
  }
}

void PrintAbsyn::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::render(char *s)
{
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}

void PrintAbsyn::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}

void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}

PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char *PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}

void PrintAbsyn::visitCmd(Cmd *p) {} //abstract class

void PrintAbsyn::visitExpCmd(ExpCmd *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitStmtCmd(StmtCmd *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->stmt_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitExp(Exp *p) {} //abstract class

void PrintAbsyn::visitEAdd(EAdd *p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->exp_1->accept(this);
  render('+');
  _i_ = 2; p->exp_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitESub(ESub *p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->exp_1->accept(this);
  render('-');
  _i_ = 2; p->exp_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEMul(EMul *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 2; p->exp_1->accept(this);
  render('*');
  _i_ = 3; p->exp_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEDiv(EDiv *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 2; p->exp_1->accept(this);
  render('/');
  _i_ = 3; p->exp_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEPow(EPow *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 3; p->exp_1->accept(this);
  render('^');
  _i_ = 4; p->exp_2->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEDice(EDice *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 0; p->expd_->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitESeqFilt(ESeqFilt *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 0; p->exp_->accept(this);
  render('[');
  if(p->listpred_) {_i_ = 0; p->listpred_->accept(this);}
  render(']');

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENeg(ENeg *p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  render('-');
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEVal(EVal *p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  _i_ = 0; p->val_->accept(this);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEList(EList *p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  render('{');
  if(p->listexp_) {_i_ = 0; p->listexp_->accept(this);}
  render('}');

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitERange(ERange *p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  render('{');
  _i_ = 0; p->range_->accept(this);
  render('}');

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKeyW(EKeyW *p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  _i_ = 0; p->expkw_->accept(this);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitECall(ECall *p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  visitIdent(p->varident_);
  render('(');
  if(p->listexp_) {_i_ = 0; p->listexp_->accept(this);}
  render(')');

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListExp(ListExp *listexp)
{
  for (ListExp::const_iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexp->end() - 1) render(',');
  }
}void PrintAbsyn::visitNumeral(Numeral *p) {} //abstract class

void PrintAbsyn::visitNumInt(NumInt *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitNumFloat(NumFloat *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitDouble(p->double_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitVal(Val *p) {} //abstract class

void PrintAbsyn::visitValNum(ValNum *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->numeral_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitValVar(ValVar *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->varident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitValStr(ValStr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitString(p->string_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitRange(Range *p) {} //abstract class

void PrintAbsyn::visitRSimple(RSimple *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_1->accept(this);
  render("..");
  _i_ = 0; p->exp_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitRStep(RStep *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_1->accept(this);
  render(',');
  _i_ = 0; p->exp_2->accept(this);
  render("..");
  _i_ = 0; p->exp_3->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitRInf(RInf *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_->accept(this);
  render("..");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitRStepInf(RStepInf *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_1->accept(this);
  render(',');
  _i_ = 0; p->exp_2->accept(this);
  render("..");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitExpD(ExpD *p) {} //abstract class

void PrintAbsyn::visitE1d6(E1d6 *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('d');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitE1dN(E1dN *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('d');
  _i_ = 4; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENd6(ENd6 *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 3; p->exp_->accept(this);
  render('d');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENdN(ENdN *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 3; p->exp_1->accept(this);
  render('d');
  _i_ = 4; p->exp_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitExpKW(ExpKW *p) {} //abstract class

void PrintAbsyn::visitEKWRepeat(EKWRepeat *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Repeat");
  _i_ = 0; p->exp_1->accept(this);
  _i_ = 0; p->exp_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKWCount(EKWCount *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Count");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKWSum(EKWSum *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Sum");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKWMean(EKWMean *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Mean");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKWSqrt(EKWSqrt *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Sqrt");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKWFloor(EKWFloor *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Floor");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKWCeil(EKWCeil *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Ceil");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKWRound(EKWRound *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Round");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKWTrunc(EKWTrunc *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Trunc");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKWAcc(EKWAcc *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Acc");
  _i_ = 0; p->exp_->accept(this);
  visitIdent(p->varident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPred(Pred *p) {} //abstract class

void PrintAbsyn::visitPredAnd(PredAnd *p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->pred_1->accept(this);
  render('&');
  _i_ = 2; p->pred_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredOr(PredOr *p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->pred_1->accept(this);
  render('|');
  _i_ = 2; p->pred_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredXOr(PredXOr *p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->pred_1->accept(this);
  render('^');
  _i_ = 2; p->pred_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredEQ(PredEQ *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  render('=');
  _i_ = 0; p->val_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredGT(PredGT *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  render('<');
  _i_ = 0; p->val_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredLT(PredLT *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  render('>');
  _i_ = 0; p->val_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredGTEq(PredGTEq *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  render("<=");
  _i_ = 0; p->val_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredLTEq(PredLTEq *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  render(">=");
  _i_ = 0; p->val_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredNot(PredNot *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  render('!');
  _i_ = 0; p->pred_->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredIsStr(PredIsStr *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  render('$');

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredIsInt(PredIsInt *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  render('#');

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredIsFloat(PredIsFloat *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  render('%');

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPredInd(PredInd *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 0; p->exp_->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListPred(ListPred *listpred)
{
  for (ListPred::const_iterator i = listpred->begin() ; i != listpred->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listpred->end() - 1) render(',');
  }
}void PrintAbsyn::visitStmt(Stmt *p) {} //abstract class

void PrintAbsyn::visitSVarAs(SVarAs *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->varident_);
  render('=');
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSVarAdd(SVarAdd *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->varident_);
  render("+=");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSVarSub(SVarSub *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->varident_);
  render("-=");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSVarMul(SVarMul *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->varident_);
  render("*=");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSVarDiv(SVarDiv *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->varident_);
  render("/=");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSFunDef(SFunDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->varident_);
  render('(');
  if(p->listexp_) {_i_ = 0; p->listexp_->accept(this);}
  render(')');
  render('=');
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}

void PrintAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}

void PrintAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}

void PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

void PrintAbsyn::visitIdent(String s)
{
  render(s);
}

void PrintAbsyn::visitVarIdent(String s)
{
  render(s);
}


ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char *ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}

void ShowAbsyn::visitCmd(Cmd *p) {} //abstract class

void ShowAbsyn::visitExpCmd(ExpCmd *p)
{
  bufAppend('(');
  bufAppend("ExpCmd");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitStmtCmd(StmtCmd *p)
{
  bufAppend('(');
  bufAppend("StmtCmd");
  bufAppend(' ');
  bufAppend('[');
  if (p->stmt_)  p->stmt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitExp(Exp *p) {} //abstract class

void ShowAbsyn::visitEAdd(EAdd *p)
{
  bufAppend('(');
  bufAppend("EAdd");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitESub(ESub *p)
{
  bufAppend('(');
  bufAppend("ESub");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEMul(EMul *p)
{
  bufAppend('(');
  bufAppend("EMul");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEDiv(EDiv *p)
{
  bufAppend('(');
  bufAppend("EDiv");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEPow(EPow *p)
{
  bufAppend('(');
  bufAppend("EPow");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEDice(EDice *p)
{
  bufAppend('(');
  bufAppend("EDice");
  bufAppend(' ');
  bufAppend('[');
  if (p->expd_)  p->expd_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitESeqFilt(ESeqFilt *p)
{
  bufAppend('(');
  bufAppend("ESeqFilt");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listpred_)  p->listpred_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitENeg(ENeg *p)
{
  bufAppend('(');
  bufAppend("ENeg");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEVal(EVal *p)
{
  bufAppend('(');
  bufAppend("EVal");
  bufAppend(' ');
  bufAppend('[');
  if (p->val_)  p->val_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEList(EList *p)
{
  bufAppend('(');
  bufAppend("EList");
  bufAppend(' ');
  bufAppend('[');
  if (p->listexp_)  p->listexp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitERange(ERange *p)
{
  bufAppend('(');
  bufAppend("ERange");
  bufAppend(' ');
  bufAppend('[');
  if (p->range_)  p->range_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitEKeyW(EKeyW *p)
{
  bufAppend('(');
  bufAppend("EKeyW");
  bufAppend(' ');
  bufAppend('[');
  if (p->expkw_)  p->expkw_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitECall(ECall *p)
{
  bufAppend('(');
  bufAppend("ECall");
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listexp_)  p->listexp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitListExp(ListExp *listexp)
{
  for (ListExp::const_iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexp->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitNumeral(Numeral *p) {} //abstract class

void ShowAbsyn::visitNumInt(NumInt *p)
{
  bufAppend('(');
  bufAppend("NumInt");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitNumFloat(NumFloat *p)
{
  bufAppend('(');
  bufAppend("NumFloat");
  bufAppend(' ');
  visitDouble(p->double_);
  bufAppend(')');
}
void ShowAbsyn::visitVal(Val *p) {} //abstract class

void ShowAbsyn::visitValNum(ValNum *p)
{
  bufAppend('(');
  bufAppend("ValNum");
  bufAppend(' ');
  bufAppend('[');
  if (p->numeral_)  p->numeral_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitValVar(ValVar *p)
{
  bufAppend('(');
  bufAppend("ValVar");
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(')');
}
void ShowAbsyn::visitValStr(ValStr *p)
{
  bufAppend('(');
  bufAppend("ValStr");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
void ShowAbsyn::visitRange(Range *p) {} //abstract class

void ShowAbsyn::visitRSimple(RSimple *p)
{
  bufAppend('(');
  bufAppend("RSimple");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitRStep(RStep *p)
{
  bufAppend('(');
  bufAppend("RStep");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(' ');
  p->exp_3->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitRInf(RInf *p)
{
  bufAppend('(');
  bufAppend("RInf");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitRStepInf(RStepInf *p)
{
  bufAppend('(');
  bufAppend("RStepInf");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitExpD(ExpD *p) {} //abstract class

void ShowAbsyn::visitE1d6(E1d6 *p)
{
  bufAppend("E1d6");
}
void ShowAbsyn::visitE1dN(E1dN *p)
{
  bufAppend('(');
  bufAppend("E1dN");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitENd6(ENd6 *p)
{
  bufAppend('(');
  bufAppend("ENd6");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitENdN(ENdN *p)
{
  bufAppend('(');
  bufAppend("ENdN");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitExpKW(ExpKW *p) {} //abstract class

void ShowAbsyn::visitEKWRepeat(EKWRepeat *p)
{
  bufAppend('(');
  bufAppend("EKWRepeat");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEKWCount(EKWCount *p)
{
  bufAppend('(');
  bufAppend("EKWCount");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKWSum(EKWSum *p)
{
  bufAppend('(');
  bufAppend("EKWSum");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKWMean(EKWMean *p)
{
  bufAppend('(');
  bufAppend("EKWMean");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKWSqrt(EKWSqrt *p)
{
  bufAppend('(');
  bufAppend("EKWSqrt");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKWFloor(EKWFloor *p)
{
  bufAppend('(');
  bufAppend("EKWFloor");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKWCeil(EKWCeil *p)
{
  bufAppend('(');
  bufAppend("EKWCeil");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKWRound(EKWRound *p)
{
  bufAppend('(');
  bufAppend("EKWRound");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKWTrunc(EKWTrunc *p)
{
  bufAppend('(');
  bufAppend("EKWTrunc");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKWAcc(EKWAcc *p)
{
  bufAppend('(');
  bufAppend("EKWAcc");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(')');
}
void ShowAbsyn::visitPred(Pred *p) {} //abstract class

void ShowAbsyn::visitPredAnd(PredAnd *p)
{
  bufAppend('(');
  bufAppend("PredAnd");
  bufAppend(' ');
  p->pred_1->accept(this);
  bufAppend(' ');
  p->pred_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitPredOr(PredOr *p)
{
  bufAppend('(');
  bufAppend("PredOr");
  bufAppend(' ');
  p->pred_1->accept(this);
  bufAppend(' ');
  p->pred_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitPredXOr(PredXOr *p)
{
  bufAppend('(');
  bufAppend("PredXOr");
  bufAppend(' ');
  p->pred_1->accept(this);
  bufAppend(' ');
  p->pred_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitPredEQ(PredEQ *p)
{
  bufAppend('(');
  bufAppend("PredEQ");
  bufAppend(' ');
  bufAppend('[');
  if (p->val_)  p->val_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitPredGT(PredGT *p)
{
  bufAppend('(');
  bufAppend("PredGT");
  bufAppend(' ');
  bufAppend('[');
  if (p->val_)  p->val_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitPredLT(PredLT *p)
{
  bufAppend('(');
  bufAppend("PredLT");
  bufAppend(' ');
  bufAppend('[');
  if (p->val_)  p->val_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitPredGTEq(PredGTEq *p)
{
  bufAppend('(');
  bufAppend("PredGTEq");
  bufAppend(' ');
  bufAppend('[');
  if (p->val_)  p->val_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitPredLTEq(PredLTEq *p)
{
  bufAppend('(');
  bufAppend("PredLTEq");
  bufAppend(' ');
  bufAppend('[');
  if (p->val_)  p->val_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitPredNot(PredNot *p)
{
  bufAppend('(');
  bufAppend("PredNot");
  bufAppend(' ');
  bufAppend('[');
  if (p->pred_)  p->pred_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitPredIsStr(PredIsStr *p)
{
  bufAppend("PredIsStr");
}
void ShowAbsyn::visitPredIsInt(PredIsInt *p)
{
  bufAppend("PredIsInt");
}
void ShowAbsyn::visitPredIsFloat(PredIsFloat *p)
{
  bufAppend("PredIsFloat");
}
void ShowAbsyn::visitPredInd(PredInd *p)
{
  bufAppend('(');
  bufAppend("PredInd");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitListPred(ListPred *listpred)
{
  for (ListPred::const_iterator i = listpred->begin() ; i != listpred->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listpred->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitStmt(Stmt *p) {} //abstract class

void ShowAbsyn::visitSVarAs(SVarAs *p)
{
  bufAppend('(');
  bufAppend("SVarAs");
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSVarAdd(SVarAdd *p)
{
  bufAppend('(');
  bufAppend("SVarAdd");
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSVarSub(SVarSub *p)
{
  bufAppend('(');
  bufAppend("SVarSub");
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSVarMul(SVarMul *p)
{
  bufAppend('(');
  bufAppend("SVarMul");
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSVarDiv(SVarDiv *p)
{
  bufAppend('(');
  bufAppend("SVarDiv");
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSFunDef(SFunDef *p)
{
  bufAppend('(');
  bufAppend("SFunDef");
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listexp_)  p->listexp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void ShowAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void ShowAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void ShowAbsyn::visitIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

void ShowAbsyn::visitVarIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}



