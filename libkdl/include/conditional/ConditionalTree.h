#ifndef CONDITIONAL_CONDITIONAL_TREE_H_
#define CONDITIONAL_CONDITIONAL_TREE_H_

#include "parser/parser.h"
#include "parser/tokens.h"

namespace kdl
{
/* 
TODO:
	See if we can detect the max parenthesis level
	to preallocate the right number of condition trees
*/


struct CNode
{
	CNode* left;
	CNode* right;

	CTokenPtr value;
	// Is something like $malfn*
	bool isMultiVar;

	CNode(CTokenPtr val)
		: left(nullptr), right(nullptr), value(val), isMultiVar(false)
	{}


};


///
/// PURPOSE
///		Hold a binary tree representing a set of conditions
///			e.g. filesize > 10MB and $malfn
/// 
///		This works by continually adding subconditions (e.g. filesize > 10MB)
///		And combining them with junctions ( 'and' or 'or' )
///		
class ConditionalTree 
{
public:
	ConditionalTree(int pLevel = 0) : m_head(nullptr), m_p_level(pLevel) {}
	~ConditionalTree();

	///
	/// PURPOSE
	///		Adds a subcondition to the tree
	/// 
	///		If the head is null, the new subcondition becomes the head
	/// 
	///		Otherwise, the subcondition becomes the head's right node
	/// 
	bool addSubCondition(CTokenPtr op, CTokenPtr left, CTokenPtr right, int pLevel);


	/// 
	/// PURPOSE
	///		Adds a junction to the tree
	/// 
	///		If the head is null, an error will be thrown
	/// 
	///		If this is a parenthisized junction, add it as the head's right node
	/// 
	///		Otherwise, the junction becomes the new head and the previous head becomes
	///		the junctions's left node	
	/// 
	bool addJunction(CTokenPtr cmpOP, int pLevel);

	bool merge(int pLevel);

	void dumpTree();

private:

	bool forwardSubCondition(CTokenPtr op, CTokenPtr left, CTokenPtr right, int pLevel);
	bool forwardJunction(CTokenPtr cmpOP, int pLevel);

	void _int_dumpTree(const CNode* head);
private:


	CNode* m_head;

	/// List of pointers to the nodes so they can be destroyed 
	std::vector<CNode*> m_nodes;

	/// Our parenthesis level
	int m_p_level;

	/// Sub Tree where additions with plevels that don't match ours 
	/// are forwarded to
	ConditionalTree* m_subTree{ nullptr };

};

} // kdl

#endif // CONDITIONAL_CONDITIONAL_TREE_H_