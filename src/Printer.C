/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2


//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
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

void PrintAbsyn::visitEKeyW(EKeyW *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->expkw_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

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

void PrintAbsyn::visitEInt(EInt *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitERange(ERange *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  render('{');
  _i_ = 0; p->val_1->accept(this);
  render("..");
  _i_ = 0; p->val_2->accept(this);
  render('}');

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitERStep(ERStep *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  render('{');
  _i_ = 0; p->val_1->accept(this);
  render(',');
  _i_ = 0; p->val_2->accept(this);
  render("..");
  _i_ = 0; p->val_3->accept(this);
  render('}');

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEList(EList *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  render('{');
  if(p->listlistmem_) {_i_ = 0; p->listlistmem_->accept(this);}
  render('}');

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

void PrintAbsyn::visitEListOp(EListOp *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 0; p->explop_->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEVar(EVar *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  visitIdent(p->varident_);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitECall(ECall *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  visitIdent(p->varident_);
  render('(');
  if(p->listexp_) {_i_ = 0; p->listexp_->accept(this);}
  render(')');

  if (oldi > 3) render(_R_PAREN);

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
  _i_ = 3; p->exp_->accept(this);

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
  _i_ = 3; p->exp_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitExpKW(ExpKW *p) {} //abstract class

void PrintAbsyn::visitEKCount(EKCount *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Count");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKSum(EKSum *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Sum");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKRepeat(EKRepeat *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Repeat");
  _i_ = 0; p->exp_1->accept(this);
  _i_ = 0; p->exp_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEKMean(EKMean *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Mean");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitPred(Pred *p) {} //abstract class

void PrintAbsyn::visitPredBranch(PredBranch *p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->pred_1->accept(this);
  render(',');
  _i_ = 2; p->pred_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

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

void PrintAbsyn::visitPredNEQ(PredNEQ *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  render("!=");
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

void PrintAbsyn::visitExpLOp(ExpLOp *p) {} //abstract class

void PrintAbsyn::visitELFilt(ELFilt *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_->accept(this);
  render('[');
  _i_ = 0; p->pred_->accept(this);
  render(']');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELSum(ELSum *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_->accept(this);
  render('[');
  render('+');
  render(']');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELAcc(ELAcc *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_->accept(this);
  render('[');
  visitIdent(p->varident_);
  render(']');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitStmt(Stmt *p) {} //abstract class

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

void PrintAbsyn::visitSFDef(SFDef *p)
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

void PrintAbsyn::visitVal(Val *p) {} //abstract class

void PrintAbsyn::visitIntVal(IntVal *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitIntNegVal(IntNegVal *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('-');
  visitInteger(p->integer_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitVarVal(VarVal *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->varident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListMem(ListMem *p) {} //abstract class

void PrintAbsyn::visitValLM(ValLM *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->val_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitStrLM(StrLM *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitString(p->string_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListExp(ListExp *listexp)
{
  for (ListExp::const_iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexp->end() - 1) render(',');
  }
}void PrintAbsyn::visitListListMem(ListListMem *listlistmem)
{
  for (ListListMem::const_iterator i = listlistmem->begin() ; i != listlistmem->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listlistmem->end() - 1) render(',');
  }
}void PrintAbsyn::visitInteger(Integer i)
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
void ShowAbsyn::visitEInt(EInt *p)
{
  bufAppend('(');
  bufAppend("EInt");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitERange(ERange *p)
{
  bufAppend('(');
  bufAppend("ERange");
  bufAppend(' ');
  p->val_1->accept(this);
  bufAppend(' ');
  p->val_2->accept(this);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitERStep(ERStep *p)
{
  bufAppend('(');
  bufAppend("ERStep");
  bufAppend(' ');
  p->val_1->accept(this);
  bufAppend(' ');
  p->val_2->accept(this);
  bufAppend(' ');
  p->val_3->accept(this);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitEList(EList *p)
{
  bufAppend('(');
  bufAppend("EList");
  bufAppend(' ');
  bufAppend('[');
  if (p->listlistmem_)  p->listlistmem_->accept(this);
  bufAppend(']');
  bufAppend(' ');
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
void ShowAbsyn::visitEListOp(EListOp *p)
{
  bufAppend('(');
  bufAppend("EListOp");
  bufAppend(' ');
  bufAppend('[');
  if (p->explop_)  p->explop_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEVar(EVar *p)
{
  bufAppend('(');
  bufAppend("EVar");
  bufAppend(' ');
  visitIdent(p->varident_);
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

void ShowAbsyn::visitEKCount(EKCount *p)
{
  bufAppend('(');
  bufAppend("EKCount");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKSum(EKSum *p)
{
  bufAppend('(');
  bufAppend("EKSum");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEKRepeat(EKRepeat *p)
{
  bufAppend('(');
  bufAppend("EKRepeat");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEKMean(EKMean *p)
{
  bufAppend('(');
  bufAppend("EKMean");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitPred(Pred *p) {} //abstract class

void ShowAbsyn::visitPredBranch(PredBranch *p)
{
  bufAppend('(');
  bufAppend("PredBranch");
  bufAppend(' ');
  p->pred_1->accept(this);
  bufAppend(' ');
  p->pred_2->accept(this);
  bufAppend(')');
}
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
void ShowAbsyn::visitPredNEQ(PredNEQ *p)
{
  bufAppend('(');
  bufAppend("PredNEQ");
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
void ShowAbsyn::visitExpLOp(ExpLOp *p) {} //abstract class

void ShowAbsyn::visitELFilt(ELFilt *p)
{
  bufAppend('(');
  bufAppend("ELFilt");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->pred_)  p->pred_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitELSum(ELSum *p)
{
  bufAppend('(');
  bufAppend("ELSum");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitELAcc(ELAcc *p)
{
  bufAppend('(');
  bufAppend("ELAcc");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(' ');
  bufAppend(')');
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
void ShowAbsyn::visitSFDef(SFDef *p)
{
  bufAppend('(');
  bufAppend("SFDef");
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
void ShowAbsyn::visitVal(Val *p) {} //abstract class

void ShowAbsyn::visitIntVal(IntVal *p)
{
  bufAppend('(');
  bufAppend("IntVal");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitIntNegVal(IntNegVal *p)
{
  bufAppend('(');
  bufAppend("IntNegVal");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitVarVal(VarVal *p)
{
  bufAppend('(');
  bufAppend("VarVal");
  bufAppend(' ');
  visitIdent(p->varident_);
  bufAppend(')');
}
void ShowAbsyn::visitListMem(ListMem *p) {} //abstract class

void ShowAbsyn::visitValLM(ValLM *p)
{
  bufAppend('(');
  bufAppend("ValLM");
  bufAppend(' ');
  bufAppend('[');
  if (p->val_)  p->val_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitStrLM(StrLM *p)
{
  bufAppend('(');
  bufAppend("StrLM");
  bufAppend(' ');
  visitString(p->string_);
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

void ShowAbsyn::visitListListMem(ListListMem *listlistmem)
{
  for (ListListMem::const_iterator i = listlistmem->begin() ; i != listlistmem->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listlistmem->end() - 1) bufAppend(", ");
  }
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



