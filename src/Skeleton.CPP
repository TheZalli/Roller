/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"



void Skeleton::visitCmd(Cmd *t) {} //abstract class
void Skeleton::visitExp(Exp *t) {} //abstract class
void Skeleton::visitNumer(Numer *t) {} //abstract class
void Skeleton::visitVal(Val *t) {} //abstract class
void Skeleton::visitExpSeq(ExpSeq *t) {} //abstract class
void Skeleton::visitExpD(ExpD *t) {} //abstract class
void Skeleton::visitExpKW(ExpKW *t) {} //abstract class
void Skeleton::visitPred(Pred *t) {} //abstract class
void Skeleton::visitExpLOp(ExpLOp *t) {} //abstract class
void Skeleton::visitStmt(Stmt *t) {} //abstract class

void Skeleton::visitExpCmd(ExpCmd *expcmd)
{
  /* Code For ExpCmd Goes Here */

  expcmd->exp_->accept(this);

}

void Skeleton::visitStmtCmd(StmtCmd *stmtcmd)
{
  /* Code For StmtCmd Goes Here */

  stmtcmd->stmt_->accept(this);

}

void Skeleton::visitEAdd(EAdd *eadd)
{
  /* Code For EAdd Goes Here */

  eadd->exp_1->accept(this);
  eadd->exp_2->accept(this);

}

void Skeleton::visitESub(ESub *esub)
{
  /* Code For ESub Goes Here */

  esub->exp_1->accept(this);
  esub->exp_2->accept(this);

}

void Skeleton::visitEMul(EMul *emul)
{
  /* Code For EMul Goes Here */

  emul->exp_1->accept(this);
  emul->exp_2->accept(this);

}

void Skeleton::visitEDiv(EDiv *ediv)
{
  /* Code For EDiv Goes Here */

  ediv->exp_1->accept(this);
  ediv->exp_2->accept(this);

}

void Skeleton::visitEVal(EVal *eval)
{
  /* Code For EVal Goes Here */

  eval->val_->accept(this);

}

void Skeleton::visitESeq(ESeq *eseq)
{
  /* Code For ESeq Goes Here */

  eseq->expseq_->accept(this);

}

void Skeleton::visitEKeyW(EKeyW *ekeyw)
{
  /* Code For EKeyW Goes Here */

  ekeyw->expkw_->accept(this);

}

void Skeleton::visitEListOp(EListOp *elistop)
{
  /* Code For EListOp Goes Here */

  elistop->explop_->accept(this);

}

void Skeleton::visitECall(ECall *ecall)
{
  /* Code For ECall Goes Here */

  visitVarIdent(ecall->varident_);
  ecall->listexp_->accept(this);

}

void Skeleton::visitIntNum(IntNum *intnum)
{
  /* Code For IntNum Goes Here */

  visitInteger(intnum->integer_);

}

void Skeleton::visitIntNegNum(IntNegNum *intnegnum)
{
  /* Code For IntNegNum Goes Here */

  visitInteger(intnegnum->integer_);

}

void Skeleton::visitValNum(ValNum *valnum)
{
  /* Code For ValNum Goes Here */

  valnum->numer_->accept(this);

}

void Skeleton::visitValVar(ValVar *valvar)
{
  /* Code For ValVar Goes Here */

  visitVarIdent(valvar->varident_);

}

void Skeleton::visitValStr(ValStr *valstr)
{
  /* Code For ValStr Goes Here */

  visitString(valstr->string_);

}

void Skeleton::visitEDiceSeq(EDiceSeq *ediceseq)
{
  /* Code For EDiceSeq Goes Here */

  ediceseq->expd_->accept(this);

}

void Skeleton::visitERange(ERange *erange)
{
  /* Code For ERange Goes Here */

  erange->val_1->accept(this);
  erange->val_2->accept(this);

}

void Skeleton::visitERStep(ERStep *erstep)
{
  /* Code For ERStep Goes Here */

  erstep->val_1->accept(this);
  erstep->val_2->accept(this);
  erstep->val_3->accept(this);

}

void Skeleton::visitEVect(EVect *evect)
{
  /* Code For EVect Goes Here */

  evect->listval_->accept(this);

}

void Skeleton::visitE1d6(E1d6 *e1d6)
{
  /* Code For E1d6 Goes Here */


}

void Skeleton::visitE1dN(E1dN *e1dn)
{
  /* Code For E1dN Goes Here */

  e1dn->exp_->accept(this);

}

void Skeleton::visitENd6(ENd6 *end6)
{
  /* Code For ENd6 Goes Here */

  end6->exp_->accept(this);

}

void Skeleton::visitENdN(ENdN *endn)
{
  /* Code For ENdN Goes Here */

  endn->exp_1->accept(this);
  endn->exp_2->accept(this);

}

void Skeleton::visitEKCount(EKCount *ekcount)
{
  /* Code For EKCount Goes Here */

  ekcount->exp_->accept(this);

}

void Skeleton::visitEKSum(EKSum *eksum)
{
  /* Code For EKSum Goes Here */

  eksum->exp_->accept(this);

}

void Skeleton::visitEKRepeat(EKRepeat *ekrepeat)
{
  /* Code For EKRepeat Goes Here */

  ekrepeat->exp_1->accept(this);
  ekrepeat->exp_2->accept(this);

}

void Skeleton::visitEKMean(EKMean *ekmean)
{
  /* Code For EKMean Goes Here */

  ekmean->exp_->accept(this);

}

void Skeleton::visitEKAcc(EKAcc *ekacc)
{
  /* Code For EKAcc Goes Here */

  ekacc->exp_->accept(this);
  visitVarIdent(ekacc->varident_);

}

void Skeleton::visitPredBranch(PredBranch *predbranch)
{
  /* Code For PredBranch Goes Here */

  predbranch->pred_1->accept(this);
  predbranch->pred_2->accept(this);

}

void Skeleton::visitPredAnd(PredAnd *predand)
{
  /* Code For PredAnd Goes Here */

  predand->pred_1->accept(this);
  predand->pred_2->accept(this);

}

void Skeleton::visitPredOr(PredOr *predor)
{
  /* Code For PredOr Goes Here */

  predor->pred_1->accept(this);
  predor->pred_2->accept(this);

}

void Skeleton::visitPredXOr(PredXOr *predxor)
{
  /* Code For PredXOr Goes Here */

  predxor->pred_1->accept(this);
  predxor->pred_2->accept(this);

}

void Skeleton::visitPredEQ(PredEQ *predeq)
{
  /* Code For PredEQ Goes Here */

  predeq->val_->accept(this);

}

void Skeleton::visitPredNEQ(PredNEQ *predneq)
{
  /* Code For PredNEQ Goes Here */

  predneq->val_->accept(this);

}

void Skeleton::visitPredGT(PredGT *predgt)
{
  /* Code For PredGT Goes Here */

  predgt->val_->accept(this);

}

void Skeleton::visitPredLT(PredLT *predlt)
{
  /* Code For PredLT Goes Here */

  predlt->val_->accept(this);

}

void Skeleton::visitPredGTEq(PredGTEq *predgteq)
{
  /* Code For PredGTEq Goes Here */

  predgteq->val_->accept(this);

}

void Skeleton::visitPredLTEq(PredLTEq *predlteq)
{
  /* Code For PredLTEq Goes Here */

  predlteq->val_->accept(this);

}

void Skeleton::visitPredIsStr(PredIsStr *predisstr)
{
  /* Code For PredIsStr Goes Here */

  predisstr->val_->accept(this);

}

void Skeleton::visitPredInd(PredInd *predind)
{
  /* Code For PredInd Goes Here */

  predind->val_->accept(this);

}

void Skeleton::visitPredRange(PredRange *predrange)
{
  /* Code For PredRange Goes Here */

  predrange->val_1->accept(this);
  predrange->val_2->accept(this);

}

void Skeleton::visitPredRStep(PredRStep *predrstep)
{
  /* Code For PredRStep Goes Here */

  predrstep->val_1->accept(this);
  predrstep->val_2->accept(this);
  predrstep->val_3->accept(this);

}

void Skeleton::visitELFilt(ELFilt *elfilt)
{
  /* Code For ELFilt Goes Here */

  elfilt->exp_->accept(this);
  elfilt->pred_->accept(this);

}

void Skeleton::visitSVarAs(SVarAs *svaras)
{
  /* Code For SVarAs Goes Here */

  visitVarIdent(svaras->varident_);
  svaras->exp_->accept(this);

}

void Skeleton::visitSFDef(SFDef *sfdef)
{
  /* Code For SFDef Goes Here */

  visitVarIdent(sfdef->varident_);
  sfdef->listexp_->accept(this);
  sfdef->exp_->accept(this);

}


void Skeleton::visitListExp(ListExp *listexp)
{
  for (ListExp::iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListVal(ListVal *listval)
{
  for (ListVal::iterator i = listval->begin() ; i != listval->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void Skeleton::visitVarIdent(VarIdent x)
{
  /* Code for VarIdent Goes Here */
}

void Skeleton::visitInteger(Integer x)
{
  /* Code for Integer Goes Here */
}

void Skeleton::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void Skeleton::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void Skeleton::visitString(String x)
{
  /* Code for String Goes Here */
}

void Skeleton::visitIdent(Ident x)
{
  /* Code for Ident Goes Here */
}



