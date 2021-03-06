#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <em.h>
#include "LLlex.h"
#include "idf.h"
#include "desig.h"
#include "node.h"
#include "scope.h"
#include "type.h"
#include "def.h"
#include "tokenname.h"

/* casestat.C */
int CaseCode(t_node *nd,label exitlabel,int end_reached);

/* chk_expr.c */
void MkCoercion(t_node **pnd,t_type *tp);
int ChkVariable(t_node **expp,int flags);
arith * MkSet(unsigned int size);
void FreeSet(arith * s);
void TryToString(t_node *nd,t_type *tp);
int ChkCall(t_node **expp);

/* code.c */
void CodeCall(t_node *nd); 
void CodeCoercion(t_type *t1,t_type *t2);
void CodeExpr(t_node *nd,t_desig *ds,label true_label,label false_label);
void CodePExpr(t_node *nd);
void RangeCheck(t_type *tpl,t_type *tpr);
void CodeConst(arith cst,int size);
void CodePString(t_node *nd,t_type *tp);
void CodeDStore(t_node *nd);

/* cstoper.c */
void cstunary(t_node **expp);
void cstibin(t_node **expp);
void cstfbin(t_node **expp);
void cstubin(t_node **expp);
void cstset(t_node **expp);
void cstcall(t_node **expp,int call);
void InitCst(void);

/* def.c */
void RemoveFromIdList(t_def *df);
void end_definition_list(t_def **pdf);
void EndProc(t_def *df,t_idf *id);
void CheckWithDef(t_def *df,t_type *tp);

/* defmodule.c */
const char * getwdir(const char *fn);
t_def * GetDefinitionModule(t_idf *id,int incr);

/* desig.c */
void CodeAddress(t_desig *ds);
void CodeDesig(t_node *nd,t_desig *ds);
void CodeValue(t_desig *ds,t_type *tp);
void LOL(arith offset,arith size);
void STL(arith offset,arith size);
void ChkForFOR(t_node *nd);
void CodeStore(t_desig *ds,t_type *tp);
void CodeMove(t_desig *rhs,t_node *left,t_type *rtp);

/* enter.c */
t_def * Enter(char *name,int kind,t_type *type,int pnam);
t_def * EnterType(char *name,t_type *type);
void EnterEnumList(t_node *Idlist,t_type *type);
void EnterFieldList(t_node *Idlist,t_type *type,t_scope *scope,arith *addr);
void EnterVarList(t_node *Idlist,t_type *type,int local);
void EnterParamList(t_param **ppr,t_node *Idlist,t_type *type,int VARp,arith *off);
void EnterExportList(t_node *Idlist,int qualified);
void CheckForImports(t_def *df);
void EnterImportList(t_node *idlist,int local,t_scope *sc);
void EnterFromImportList(t_node *idlist,t_def *FromDef,t_node *FromId);

/* error.c */
void error(char *fmt, ...);
void node_error(t_node *node, char *fmt, ...);
void warning(int class, char *fmt, ...);
void node_warning(t_node *node, int class, char *fmt, ...);
void lexerror(char *fmt, ...);
void lexwarning(int class, char *fmt, ...);
void fatal(char *fmt, ...);
void crash(char *fmt, ...);

/* LLlex.c */
void CheckForLineDirective(void);
int LLlex(void);

/* Lpars.c */
void CompUnit(void);
void DefModule(void);

/* main.c */
void do_SYSTEM(void);

/* misc.c */
void match_id(t_idf *id1,t_idf *id2);
t_idf * gen_anon_idf(void);
void not_declared(char *what,t_node *id,char *where);

/* node.c */
void FreeNode(t_node *nd);
int NodeCrash(t_node *expp,label,int);
int PNodeCrash(t_node **expp,int);

/* options.c */
void DoOption(char *text);

/* scope.C */
void open_scope(int scopetype);
void Reverse(t_def **pdf);
void close_scope(int flag);
void InitScope(void);

/* stab.c */
void stb_addtp(char *s,t_type *tp);
void stb_string(t_def *df,int kind);

/* sym2str - generated by tokcase.awk */
char * symbol2str(int);

/* tmpvar.C */
void TmpOpen(t_scope *sc);
arith TmpSpace(arith sz,int al);
arith NewInt(void);
arith NewPtr(void);
void FreeInt(arith off);
void FreePtr(arith off);
void TmpClose(void);

/* tokenname.c */
void reserve(struct tokenname *resv);

/* type.c */
void ArrayElSize(t_type *tp);
void InitTypes(void);
int fit(arith sz,int nbytes);
void SolveForwardTypeRefs(t_def *df);
void ForceForwardTypeDef(t_def *df);
int chk_bounds(arith l1,arith l2,int fund);
int in_range(arith i,t_type *tp);
void getbounds(t_type *tp,arith *plo,arith *phi);
void genrck(t_type *tp);
void ArraySizes(t_type *tp);
void FreeType(t_type *tp);
void DeclareType(t_node *nd,t_def *df,t_type *tp);
int type_or_forward(t_type *tp);
int lcm(int m,int n);

/* typequiv.c */
int TstProcEquiv(t_type *tp1,t_type *tp2);
int TstCompat(t_type *tp1,t_type *tp2);
int TstAssCompat(t_type *tp1,t_type *tp2);
char * incompat(t_type *tp1,t_type *tp2);
int TstParCompat(int parno,t_type *formaltype,int VARflag,t_node **nd,t_def *edf);
int ChkAssCompat(t_node **nd,t_type *tp,char *message);
int ChkCompat(t_node **nd,t_type *tp,char *message);

/* walk.c */
void def_ilb(label l);
int LblWalkNode(label lbl,t_node *nd,int exit,int reach);
void DoLineno(t_node *nd);
void DoFilename(int needed);
void WalkModule(t_def *module);


