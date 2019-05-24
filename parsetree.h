/*
 * parsetree.h
 */

#ifndef PARSETREE_H_
#define PARSETREE_H_

#include <vector>
#include <map>
using std::vector;
using std::map;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

// a "forward declaration" for a class to hold values
class Value;

class ParseTree {
    int            linenum;
    ParseTree    *left;
    ParseTree    *right;
    
public:
    ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)
    : linenum(linenum), left(l), right(r) {}
    
    virtual ~ParseTree() {
        delete left;
        delete right;
    }
    
    int GetLineNumber() const { return linenum; }
    
    virtual NodeType GetType() const { return ERRTYPE; }
    
    int LeafCount() const {
        int lc = 0;
        if( left ) lc += left->LeafCount();
        if( right ) lc += right->LeafCount();
        if( left == 0 && right == 0 )
            lc++;
        return lc;
    }
    
    virtual bool IsIdent() const { return false; }
    virtual bool IsVar() const { return false; }
    virtual string GetId() const { return ""; }
    
    int IdentCount() const {
        int cnt = 0;
        if( left ) cnt += left->IdentCount();
        if( right ) cnt += right->IdentCount();
        if( IsIdent() )
            cnt++;
        return cnt;
    }
    
    void GetVars(map<string,bool>& var) {
        if( left ) left->GetVars(var);
        if( right ) right->GetVars(var);
        if( IsVar() )
            var[ this->GetId() ] = true;
    }
};

class StmtList : public ParseTree {
    
public:
    StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}
    
};

class VarDecl : public ParseTree {
    string id;
    
public:
    VarDecl(Token& t, ParseTree *ex) : ParseTree(t.GetLinenum(), ex), id(t.GetLexeme()) {}
    
    bool IsVar() const { return true; }
    string GetId() const { return id; }
};

class Assignment : public ParseTree {
    string id;
    
public:
    Assignment(Token& t, ParseTree *e) : ParseTree(t.GetLinenum(), e), id(t.GetLexeme()) {}
};

class Print : public ParseTree {
public:
    Print(int line, ParseTree *e) : ParseTree(line, e) {}
};

class Repeat : public ParseTree {
    
public:
    Repeat(int line, ParseTree *e, ParseTree *s) : ParseTree(line, e, s) {}
};


class PlusExpr : public ParseTree {
public:
    PlusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class MinusExpr : public ParseTree {
public:
    MinusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class TimesExpr : public ParseTree {
public:
    TimesExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class SliceExpr : public ParseTree {
public:
    SliceExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class SliceOperand : public ParseTree {
public:
    SliceOperand(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class IConst : public ParseTree {
    int val;
    
public:
    IConst(Token& t) : ParseTree(t.GetLinenum()) {
        val = stoi(t.GetLexeme());
    }
    
    NodeType GetType() const { return INTTYPE; }
};

class SConst : public ParseTree {
    string val;
    
public:
    SConst(Token& t) : ParseTree(t.GetLinenum()) {
        val = t.GetLexeme();
    }
    
    NodeType GetType() const { return STRTYPE; }
};

class Ident : public ParseTree {
    string id;
    
public:
    Ident(Token& t) : ParseTree(t.GetLinenum()), id(t.GetLexeme()) {}
    
    bool IsIdent() const { return true; }
    string GetId() const { return id; }
};

#endif /* PARSETREE_H_ */
