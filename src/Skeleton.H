#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"


class Skeleton : public Visitor
{
public:
  void visitCmd(Cmd *p);
  void visitExp(Exp *p);
  void visitNumeral(Numeral *p);
  void visitVal(Val *p);
  void visitRange(Range *p);
  void visitExpD(ExpD *p);
  void visitExpKW(ExpKW *p);
  void visitPred(Pred *p);
  void visitStmt(Stmt *p);
  void visitExpCmd(ExpCmd *p);
  void visitStmtCmd(StmtCmd *p);
  void visitEAdd(EAdd *p);
  void visitESub(ESub *p);
  void visitEMul(EMul *p);
  void visitEDiv(EDiv *p);
  void visitEPow(EPow *p);
  void visitENeg(ENeg *p);
  void visitNumInt(NumInt *p);
  void visitNumFloat(NumFloat *p);
  void visitEVal(EVal *p);
  void visitValNum(ValNum *p);
  void visitValVar(ValVar *p);
  void visitValStr(ValStr *p);
  void visitEList(EList *p);
  void visitERange(ERange *p);
  void visitRSimple(RSimple *p);
  void visitRStep(RStep *p);
  void visitRInf(RInf *p);
  void visitRStepInf(RStepInf *p);
  void visitEDice(EDice *p);
  void visitE1d6(E1d6 *p);
  void visitE1dN(E1dN *p);
  void visitENd6(ENd6 *p);
  void visitENdN(ENdN *p);
  void visitEKeyW(EKeyW *p);
  void visitEKWRepeat(EKWRepeat *p);
  void visitEKWCount(EKWCount *p);
  void visitEKWSum(EKWSum *p);
  void visitEKWMean(EKWMean *p);
  void visitEKWSqrt(EKWSqrt *p);
  void visitEKWFloor(EKWFloor *p);
  void visitEKWCeil(EKWCeil *p);
  void visitEKWRound(EKWRound *p);
  void visitEKWTrunc(EKWTrunc *p);
  void visitEKWAcc(EKWAcc *p);
  void visitPredAnd(PredAnd *p);
  void visitPredOr(PredOr *p);
  void visitPredXOr(PredXOr *p);
  void visitPredEQ(PredEQ *p);
  void visitPredGT(PredGT *p);
  void visitPredLT(PredLT *p);
  void visitPredGTEq(PredGTEq *p);
  void visitPredLTEq(PredLTEq *p);
  void visitPredNot(PredNot *p);
  void visitPredIsStr(PredIsStr *p);
  void visitPredIsInt(PredIsInt *p);
  void visitPredIsFloat(PredIsFloat *p);
  void visitPredInd(PredInd *p);
  void visitESeqFilt(ESeqFilt *p);
  void visitECall(ECall *p);
  void visitSVarAs(SVarAs *p);
  void visitSVarAdd(SVarAdd *p);
  void visitSVarSub(SVarSub *p);
  void visitSVarMul(SVarMul *p);
  void visitSVarDiv(SVarDiv *p);
  void visitSFunDef(SFunDef *p);
  void visitListExp(ListExp *p);
  void visitListPred(ListPred *p);

  void visitVarIdent(VarIdent x);
  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);

};


#endif
