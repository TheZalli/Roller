/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Evaluator.H"


void Evaluator::visitCmd(Cmd *t) {} //abstract class
void Evaluator::visitExp(Exp *t) {} //abstract class
void Evaluator::visitNumeral(Numeral *t) {} //abstract class
void Evaluator::visitVal(Val *t) {} //abstract class
void Evaluator::visitRange(Range *t) {} //abstract class
void Evaluator::visitExpD(ExpD *t) {} //abstract class
void Evaluator::visitExpKW(ExpKW *t) {} //abstract class
void Evaluator::visitPred(Pred *t) {} //abstract class
void Evaluator::visitStmt(Stmt *t) {} //abstract class

void Evaluator::visitExpCmd(ExpCmd *expcmd)
{
	/* Code For ExpCmd Goes Here */
	
	expcmd->exp_->accept(this);
	
}

void Evaluator::visitStmtCmd(StmtCmd *stmtcmd)
{
	/* Code For StmtCmd Goes Here */
	
	stmtcmd->stmt_->accept(this);
	
}

void Evaluator::visitEAdd(EAdd *eadd)
{
	/* Code For EAdd Goes Here */
	
	eadd->exp_1->accept(this);
	eadd->exp_2->accept(this);
	
}

void Evaluator::visitESub(ESub *esub)
{
	/* Code For ESub Goes Here */
	
	esub->exp_1->accept(this);
	esub->exp_2->accept(this);
	
}

void Evaluator::visitEMul(EMul *emul)
{
	/* Code For EMul Goes Here */
	
	emul->exp_1->accept(this);
	emul->exp_2->accept(this);
	
}

void Evaluator::visitEDiv(EDiv *ediv)
{
	/* Code For EDiv Goes Here */
	
	ediv->exp_1->accept(this);
	ediv->exp_2->accept(this);
	
}

void Evaluator::visitEPow(EPow *epow)
{
	/* Code For EPow Goes Here */
	
	epow->exp_1->accept(this);
	epow->exp_2->accept(this);
	
}

void Evaluator::visitENeg(ENeg *eneg)
{
	/* Code For ENeg Goes Here */
	
	eneg->exp_->accept(this);
	
}

void Evaluator::visitEVal(EVal *eval)
{
	/* Code For EVal Goes Here */
	
	eval->val_->accept(this);
	
}

void Evaluator::visitEList(EList *elist)
{
	/* Code For EList Goes Here */
	
	elist->listexp_->accept(this);
	
}

void Evaluator::visitERange(ERange *erange)
{
	/* Code For ERange Goes Here */
	
	erange->range_->accept(this);
	
}

void Evaluator::visitEDice(EDice *edice)
{
	/* Code For EDice Goes Here */
	
	edice->expd_->accept(this);
	
}

void Evaluator::visitEKeyW(EKeyW *ekeyw)
{
	/* Code For EKeyW Goes Here */
	
	ekeyw->expkw_->accept(this);
	
}

void Evaluator::visitESeqFilt(ESeqFilt *eseqfilt)
{
	/* Code For ESeqFilt Goes Here */
	
	eseqfilt->exp_->accept(this);
	eseqfilt->listpred_->accept(this);
	
}

void Evaluator::visitECall(ECall *ecall)
{
	/* Code For ECall Goes Here */
	
	visitVarIdent(ecall->varident_);
	ecall->listexp_->accept(this);
	
}

void Evaluator::visitNumInt(NumInt *numint)
{
	/* Code For NumInt Goes Here */
	
	visitInteger(numint->integer_);
	
}

void Evaluator::visitNumFloat(NumFloat *numfloat)
{
	/* Code For NumFloat Goes Here */
	
	visitDouble(numfloat->double_);
	
}

void Evaluator::visitValNum(ValNum *valnum)
{
	/* Code For ValNum Goes Here */
	
	valnum->numeral_->accept(this);
	
}

void Evaluator::visitValVar(ValVar *valvar)
{
	/* Code For ValVar Goes Here */
	
	visitVarIdent(valvar->varident_);
	
}

void Evaluator::visitValStr(ValStr *valstr)
{
	/* Code For ValStr Goes Here */
	
	visitString(valstr->string_);
	
}

void Evaluator::visitRSimple(RSimple *rsimple)
{
	/* Code For RSimple Goes Here */
	
	rsimple->exp_1->accept(this);
	rsimple->exp_2->accept(this);
	
}

void Evaluator::visitRStep(RStep *rstep)
{
	/* Code For RStep Goes Here */
	
	rstep->exp_1->accept(this);
	rstep->exp_2->accept(this);
	rstep->exp_3->accept(this);
	
}

void Evaluator::visitRInf(RInf *rinf)
{
	/* Code For RInf Goes Here */
	
	rinf->exp_->accept(this);
	
}

void Evaluator::visitRStepInf(RStepInf *rstepinf)
{
	/* Code For RStepInf Goes Here */
	
	rstepinf->exp_1->accept(this);
	rstepinf->exp_2->accept(this);
	
}

void Evaluator::visitE1d6(E1d6 *e1d6)
{
	/* Code For E1d6 Goes Here */
	
	
}

void Evaluator::visitE1dN(E1dN *e1dn)
{
	/* Code For E1dN Goes Here */
	
	e1dn->exp_->accept(this);
	
}

void Evaluator::visitENd6(ENd6 *end6)
{
	/* Code For ENd6 Goes Here */
	
	end6->exp_->accept(this);
	
}

void Evaluator::visitENdN(ENdN *endn)
{
	/* Code For ENdN Goes Here */
	
	endn->exp_1->accept(this);
	endn->exp_2->accept(this);
	
}

void Evaluator::visitEKWRepeat(EKWRepeat *ekwrepeat)
{
	/* Code For EKWRepeat Goes Here */
	
	ekwrepeat->exp_1->accept(this);
	ekwrepeat->exp_2->accept(this);
	
}

void Evaluator::visitEKWCount(EKWCount *ekwcount)
{
	/* Code For EKWCount Goes Here */
	
	ekwcount->exp_->accept(this);
	
}

void Evaluator::visitEKWSum(EKWSum *ekwsum)
{
	/* Code For EKWSum Goes Here */
	
	ekwsum->exp_->accept(this);
	
}

void Evaluator::visitEKWMean(EKWMean *ekwmean)
{
	/* Code For EKWMean Goes Here */
	
	ekwmean->exp_->accept(this);
	
}

void Evaluator::visitEKWSqrt(EKWSqrt *ekwsqrt)
{
	/* Code For EKWSqrt Goes Here */
	
	ekwsqrt->exp_->accept(this);
	
}

void Evaluator::visitEKWFloor(EKWFloor *ekwfloor)
{
	/* Code For EKWFloor Goes Here */
	
	ekwfloor->exp_->accept(this);
	
}

void Evaluator::visitEKWCeil(EKWCeil *ekwceil)
{
	/* Code For EKWCeil Goes Here */
	
	ekwceil->exp_->accept(this);
	
}

void Evaluator::visitEKWRound(EKWRound *ekwround)
{
	/* Code For EKWRound Goes Here */
	
	ekwround->exp_->accept(this);
	
}

void Evaluator::visitEKWTrunc(EKWTrunc *ekwtrunc)
{
	/* Code For EKWTrunc Goes Here */
	
	ekwtrunc->exp_->accept(this);
	
}

void Evaluator::visitEKWAcc(EKWAcc *ekwacc)
{
	/* Code For EKWAcc Goes Here */
	
	ekwacc->exp_->accept(this);
	visitVarIdent(ekwacc->varident_);
	
}

void Evaluator::visitPredAnd(PredAnd *predand)
{
	/* Code For PredAnd Goes Here */
	
	predand->pred_1->accept(this);
	predand->pred_2->accept(this);
	
}

void Evaluator::visitPredOr(PredOr *predor)
{
	/* Code For PredOr Goes Here */
	
	predor->pred_1->accept(this);
	predor->pred_2->accept(this);
	
}

void Evaluator::visitPredXOr(PredXOr *predxor)
{
	/* Code For PredXOr Goes Here */
	
	predxor->pred_1->accept(this);
	predxor->pred_2->accept(this);
	
}

void Evaluator::visitPredEQ(PredEQ *predeq)
{
	/* Code For PredEQ Goes Here */
	
	predeq->val_->accept(this);
	
}

void Evaluator::visitPredGT(PredGT *predgt)
{
	/* Code For PredGT Goes Here */
	
	predgt->val_->accept(this);
	
}

void Evaluator::visitPredLT(PredLT *predlt)
{
	/* Code For PredLT Goes Here */
	
	predlt->val_->accept(this);
	
}

void Evaluator::visitPredGTEq(PredGTEq *predgteq)
{
	/* Code For PredGTEq Goes Here */
	
	predgteq->val_->accept(this);
	
}

void Evaluator::visitPredLTEq(PredLTEq *predlteq)
{
	/* Code For PredLTEq Goes Here */
	
	predlteq->val_->accept(this);
	
}

void Evaluator::visitPredNot(PredNot *prednot)
{
	/* Code For PredNot Goes Here */
	
	prednot->pred_->accept(this);
	
}

void Evaluator::visitPredIsStr(PredIsStr *predisstr)
{
	/* Code For PredIsStr Goes Here */
	
	
}

void Evaluator::visitPredIsInt(PredIsInt *predisint)
{
	/* Code For PredIsInt Goes Here */
	
	
}

void Evaluator::visitPredIsFloat(PredIsFloat *predisfloat)
{
	/* Code For PredIsFloat Goes Here */
	
	
}

void Evaluator::visitPredInd(PredInd *predind)
{
	/* Code For PredInd Goes Here */
	
	predind->exp_->accept(this);
	
}

void Evaluator::visitSVarAs(SVarAs *svaras)
{
	/* Code For SVarAs Goes Here */
	
	visitVarIdent(svaras->varident_);
	svaras->exp_->accept(this);
	
}

void Evaluator::visitSVarAdd(SVarAdd *svaradd)
{
	/* Code For SVarAdd Goes Here */
	
	visitVarIdent(svaradd->varident_);
	svaradd->exp_->accept(this);
	
}

void Evaluator::visitSVarSub(SVarSub *svarsub)
{
	/* Code For SVarSub Goes Here */
	
	visitVarIdent(svarsub->varident_);
	svarsub->exp_->accept(this);
	
}

void Evaluator::visitSVarMul(SVarMul *svarmul)
{
	/* Code For SVarMul Goes Here */
	
	visitVarIdent(svarmul->varident_);
	svarmul->exp_->accept(this);
	
}

void Evaluator::visitSVarDiv(SVarDiv *svardiv)
{
	/* Code For SVarDiv Goes Here */
	
	visitVarIdent(svardiv->varident_);
	svardiv->exp_->accept(this);
	
}

void Evaluator::visitSFunDef(SFunDef *sfundef)
{
	/* Code For SFunDef Goes Here */
	
	visitVarIdent(sfundef->varident_);
	sfundef->listexp_->accept(this);
	sfundef->exp_->accept(this);
	
}


void Evaluator::visitListExp(ListExp *listexp)
{
	for (ListExp::iterator i = listexp->begin() ; i != listexp->end() ; ++i)
	{
		(*i)->accept(this);
	}
}

void Evaluator::visitListPred(ListPred *listpred)
{
	for (ListPred::iterator i = listpred->begin() ; i != listpred->end() ; ++i)
	{
		(*i)->accept(this);
	}
}


void Evaluator::visitVarIdent(VarIdent x)
{
	/* Code for VarIdent Goes Here */
}

void Evaluator::visitInteger(Integer x)
{
	/* Code for Integer Goes Here */
}

void Evaluator::visitChar(Char x)
{
	/* Code for Char Goes Here */
}

void Evaluator::visitDouble(Double x)
{
	/* Code for Double Goes Here */
}

void Evaluator::visitString(String x)
{
	/* Code for String Goes Here */
}

void Evaluator::visitIdent(Ident x)
{
	/* Code for Ident Goes Here */
}



/*
ExprType ExprType::show(std::ostream out) const
{
	switch (type) {
		case exptypes.Integer:
			out << Integer;
		break;
		default:
		break;
	}
}
*/
