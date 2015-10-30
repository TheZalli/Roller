/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"



void Skeleton::visitCmd(Cmd *t) {} //abstract class
void Skeleton::visitExp(Exp *t) {} //abstract class
void Skeleton::visitNumeral(Numeral *t) {} //abstract class
void Skeleton::visitVal(Val *t) {} //abstract class
void Skeleton::visitRange(Range *t) {} //abstract class
void Skeleton::visitExpD(ExpD *t) {} //abstract class
void Skeleton::visitExpKW(ExpKW *t) {} //abstract class
void Skeleton::visitPred(Pred *t) {} //abstract class
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

void Skeleton::visitEPow(EPow *epow)
{
  /* Code For EPow Goes Here */

  epow->exp_1->accept(this);
  epow->exp_2->accept(this);

}

void Skeleton::visitENeg(ENeg *eneg)
{
  /* Code For ENeg Goes Here */

  eneg->exp_->accept(this);

}

void Skeleton::visitEVal(EVal *eval)
{
  /* Code For EVal Goes Here */

  eval->val_->accept(this);

}

void Skeleton::visitEList(EList *elist)
{
  /* Code For EList Goes Here */

  elist->listexp_->accept(this);

}

void Skeleton::visitERange(ERange *erange)
{
  /* Code For ERange Goes Here */

  erange->range_->accept(this);

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

void Skeleton::visitESeqFilt(ESeqFilt *eseqfilt)
{
  /* Code For ESeqFilt Goes Here */

  eseqfilt->exp_->accept(this);
  eseqfilt->listpred_->accept(this);

}

void Skeleton::visitECall(ECall *ecall)
{
  /* Code For ECall Goes Here */

  visitVarIdent(ecall->varident_);
  ecall->listexp_->accept(this);

}

void Skeleton::visitNumInt(NumInt *numint)
{
  /* Code For NumInt Goes Here */

  visitInteger(numint->integer_);

}

void Skeleton::visitNumFloat(NumFloat *numfloat)
{
  /* Code For NumFloat Goes Here */

  visitDouble(numfloat->double_);

}

void Skeleton::visitValNum(ValNum *valnum)
{
  /* Code For ValNum Goes Here */

  valnum->numeral_->accept(this);

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

void Skeleton::visitRSimple(RSimple *rsimple)
{
  /* Code For RSimple Goes Here */

  rsimple->exp_1->accept(this);
  rsimple->exp_2->accept(this);

}

void Skeleton::visitRStep(RStep *rstep)
{
  /* Code For RStep Goes Here */

  rstep->exp_1->accept(this);
  rstep->exp_2->accept(this);
  rstep->exp_3->accept(this);

}

void Skeleton::visitRInf(RInf *rinf)
{
  /* Code For RInf Goes Here */

  rinf->exp_->accept(this);

}

void Skeleton::visitRStepInf(RStepInf *rstepinf)
{
  /* Code For RStepInf Goes Here */

  rstepinf->exp_1->accept(this);
  rstepinf->exp_2->accept(this);

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

void Skeleton::visitEKWRepeat(EKWRepeat *ekwrepeat)
{
  /* Code For EKWRepeat Goes Here */

  ekwrepeat->exp_1->accept(this);
  ekwrepeat->exp_2->accept(this);

}

void Skeleton::visitEKWCount(EKWCount *ekwcount)
{
  /* Code For EKWCount Goes Here */

  ekwcount->exp_->accept(this);

}

void Skeleton::visitEKWSum(EKWSum *ekwsum)
{
  /* Code For EKWSum Goes Here */

  ekwsum->exp_->accept(this);

}

void Skeleton::visitEKWMean(EKWMean *ekwmean)
{
  /* Code For EKWMean Goes Here */

  ekwmean->exp_->accept(this);

}

void Skeleton::visitEKWSqrt(EKWSqrt *ekwsqrt)
{
  /* Code For EKWSqrt Goes Here */

  ekwsqrt->exp_->accept(this);

}

void Skeleton::visitEKWFloor(EKWFloor *ekwfloor)
{
  /* Code For EKWFloor Goes Here */

  ekwfloor->exp_->accept(this);

}

void Skeleton::visitEKWCeil(EKWCeil *ekwceil)
{
  /* Code For EKWCeil Goes Here */

  ekwceil->exp_->accept(this);

}

void Skeleton::visitEKWRound(EKWRound *ekwround)
{
  /* Code For EKWRound Goes Here */

  ekwround->exp_->accept(this);

}

void Skeleton::visitEKWTrunc(EKWTrunc *ekwtrunc)
{
  /* Code For EKWTrunc Goes Here */

  ekwtrunc->exp_->accept(this);

}

void Skeleton::visitEKWAcc(EKWAcc *ekwacc)
{
  /* Code For EKWAcc Goes Here */

  ekwacc->exp_->accept(this);
  visitVarIdent(ekwacc->varident_);

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

void Skeleton::visitPredNot(PredNot *prednot)
{
  /* Code For PredNot Goes Here */

  prednot->pred_->accept(this);

}

void Skeleton::visitPredIsStr(PredIsStr *predisstr)
{
  /* Code For PredIsStr Goes Here */


}

void Skeleton::visitPredIsInt(PredIsInt *predisint)
{
  /* Code For PredIsInt Goes Here */


}

void Skeleton::visitPredIsFloat(PredIsFloat *predisfloat)
{
  /* Code For PredIsFloat Goes Here */


}

void Skeleton::visitPredInd(PredInd *predind)
{
  /* Code For PredInd Goes Here */

  predind->exp_->accept(this);

}

void Skeleton::visitSVarAs(SVarAs *svaras)
{
  /* Code For SVarAs Goes Here */

  visitVarIdent(svaras->varident_);
  svaras->exp_->accept(this);

}

void Skeleton::visitSVarAdd(SVarAdd *svaradd)
{
  /* Code For SVarAdd Goes Here */

  visitVarIdent(svaradd->varident_);
  svaradd->exp_->accept(this);

}

void Skeleton::visitSVarSub(SVarSub *svarsub)
{
  /* Code For SVarSub Goes Here */

  visitVarIdent(svarsub->varident_);
  svarsub->exp_->accept(this);

}

void Skeleton::visitSVarMul(SVarMul *svarmul)
{
  /* Code For SVarMul Goes Here */

  visitVarIdent(svarmul->varident_);
  svarmul->exp_->accept(this);

}

void Skeleton::visitSVarDiv(SVarDiv *svardiv)
{
  /* Code For SVarDiv Goes Here */

  visitVarIdent(svardiv->varident_);
  svardiv->exp_->accept(this);

}

void Skeleton::visitSFunDef(SFunDef *sfundef)
{
  /* Code For SFunDef Goes Here */

  visitVarIdent(sfundef->varident_);
  sfundef->listexp_->accept(this);
  sfundef->exp_->accept(this);

}


void Skeleton::visitListExp(ListExp *listexp)
{
  for (ListExp::iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListPred(ListPred *listpred)
{
  for (ListPred::iterator i = listpred->begin() ; i != listpred->end() ; ++i)
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



