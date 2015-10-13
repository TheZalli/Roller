#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"


class Skeleton : public Visitor
{
public:
  void visitCmd(Cmd *p);
  void visitExp(Exp *p);
  void visitExpD(ExpD *p);
  void visitExpKW(ExpKW *p);
  void visitPred(Pred *p);
  void visitExpLOp(ExpLOp *p);
  void visitStmt(Stmt *p);
  void visitVal(Val *p);
  void visitListMem(ListMem *p);
  void visitExpCmd(ExpCmd *p);
  void visitStmtCmd(StmtCmd *p);
  void visitEAdd(EAdd *p);
  void visitESub(ESub *p);
  void visitEMul(EMul *p);
  void visitEDiv(EDiv *p);
  void visitEInt(EInt *p);
  void visitERange(ERange *p);
  void visitERStep(ERStep *p);
  void visitEList(EList *p);
  void visitEDice(EDice *p);
  void visitE1d6(E1d6 *p);
  void visitE1dN(E1dN *p);
  void visitENd6(ENd6 *p);
  void visitENdN(ENdN *p);
  void visitEKeyW(EKeyW *p);
  void visitEKCount(EKCount *p);
  void visitEKSum(EKSum *p);
  void visitEKRepeat(EKRepeat *p);
  void visitEKMean(EKMean *p);
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
  void visitEListOp(EListOp *p);
  void visitELFilt(ELFilt *p);
  void visitELSum(ELSum *p);
  void visitELAcc(ELAcc *p);
  void visitSVarAs(SVarAs *p);
  void visitSFDef(SFDef *p);
  void visitEVar(EVar *p);
  void visitECall(ECall *p);
  void visitIntVal(IntVal *p);
  void visitIntNegVal(IntNegVal *p);
  void visitVarVal(VarVal *p);
  void visitValLM(ValLM *p);
  void visitStrLM(StrLM *p);
  void visitListParamIdent(ListParamIdent *p);
  void visitListExp(ListExp *p);
  void visitListListMem(ListListMem *p);

  void visit"VarIdent"("VarIdent" x);
  void visit"ParamIdent"("ParamIdent" x);
  void visit"FunIdent"("FunIdent" x);
  void visit"Integer"("Integer" x);
  void visit"Char"("Char" x);
  void visit"Double"("Double" x);
  void visit"String"("String" x);
  void visit"Ident"("Ident" x);

};


#endif
