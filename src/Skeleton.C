/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"



void Skeleton::visitCmd(Cmd *t) {} //abstract class
void Skeleton::visitExp(Exp *t) {} //abstract class
void Skeleton::visitExpD(ExpD *t) {} //abstract class
void Skeleton::visitExpKW(ExpKW *t) {} //abstract class
void Skeleton::visitPred(Pred *t) {} //abstract class
void Skeleton::visitExpLOp(ExpLOp *t) {} //abstract class
void Skeleton::visitStmt(Stmt *t) {} //abstract class
void Skeleton::visitVal(Val *t) {} //abstract class
void Skeleton::visitListMem(ListMem *t) {} //abstract class

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

void Skeleton::visitEInt(EInt *eint)
{
  /* Code For EInt Goes Here */

  visitInteger(eint->integer_);

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

void Skeleton::visitEList(EList *elist)
{
  /* Code For EList Goes Here */

  elist->listlistmem_->accept(this);

}

void Skeleton::visitEDice(EDice *edice)
{
  /* Code For EDice Goes Here */

  edice->expd_->accept(this);

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

void Skeleton::visitEVar(EVar *evar)
{
  /* Code For EVar Goes Here */

  visitVarIdent(evar->varident_);

}

void Skeleton::visitECall(ECall *ecall)
{
  /* Code For ECall Goes Here */

  visitFunIdent(ecall->funident_);
  ecall->listexp_->accept(this);

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

  visitInteger(ekrepeat->integer_);
  ekrepeat->exp_->accept(this);

}

void Skeleton::visitEKMean(EKMean *ekmean)
{
  /* Code For EKMean Goes Here */

  ekmean->exp_->accept(this);

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

void Skeleton::visitELFilt(ELFilt *elfilt)
{
  /* Code For ELFilt Goes Here */

  elfilt->exp_->accept(this);
  elfilt->pred_->accept(this);

}

void Skeleton::visitELSum(ELSum *elsum)
{
  /* Code For ELSum Goes Here */

  elsum->exp_->accept(this);

}

void Skeleton::visitELAcc(ELAcc *elacc)
{
  /* Code For ELAcc Goes Here */

  elacc->exp_->accept(this);
  visitFunIdent(elacc->funident_);

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

  visitFunIdent(sfdef->funident_);
  sfdef->listparamident_->accept(this);
  sfdef->exp_->accept(this);

}

void Skeleton::visitIntVal(IntVal *intval)
{
  /* Code For IntVal Goes Here */

  visitInteger(intval->integer_);

}

void Skeleton::visitIntNegVal(IntNegVal *intnegval)
{
  /* Code For IntNegVal Goes Here */

  visitInteger(intnegval->integer_);

}

void Skeleton::visitVarVal(VarVal *varval)
{
  /* Code For VarVal Goes Here */

  visitVarIdent(varval->varident_);

}

void Skeleton::visitValLM(ValLM *vallm)
{
  /* Code For ValLM Goes Here */

  vallm->val_->accept(this);

}

void Skeleton::visitStrLM(StrLM *strlm)
{
  /* Code For StrLM Goes Here */

  visitString(strlm->string_);

}


void Skeleton::visitListParamIdent(ListParamIdent *listparamident)
{
  for (ListParamIdent::iterator i = listparamident->begin() ; i != listparamident->end() ; ++i)
  {
    visitParamIdent(*i) ;
  }
}

void Skeleton::visitListExp(ListExp *listexp)
{
  for (ListExp::iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListListMem(ListListMem *listlistmem)
{
  for (ListListMem::iterator i = listlistmem->begin() ; i != listlistmem->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void Skeleton::visitVarIdent(VarIdent x)
{
  /* Code for VarIdent Goes Here */
}

void Skeleton::visitParamIdent(ParamIdent x)
{
  /* Code for ParamIdent Goes Here */
}

void Skeleton::visitFunIdent(FunIdent x)
{
  /* Code for FunIdent Goes Here */
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



