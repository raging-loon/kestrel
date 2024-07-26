#include "conditional/ConditionalTree.h"

using kdl::CNode;
using kdl::CTokenPtr;
using kdl::ConditionalTree;
using kdl::token_t;

ConditionalTree::~ConditionalTree()
{
	if (m_p_level == 0)
	{
		for (int i = 0; i < m_nodes.size(); i++)
			delete m_nodes[i];

	}

	if (m_subTree)
	{
		delete m_subTree;
	}
}

bool ConditionalTree::addSubCondition(CTokenPtr op, CTokenPtr left, CTokenPtr right, int pLevel)
{
	if (!op || !left || !right)
		return false;


	auto* nnode = new CNode(op);

	nnode->left = new CNode(left);


	nnode->right = new CNode(right);

	m_nodes.push_back(nnode);
	m_nodes.push_back(nnode->left);
	m_nodes.push_back(nnode->right);

	if (pLevel != m_p_level)
		return forwardSubCondition(op, left, right, pLevel);
	

	if (!m_head)
		m_head = nnode;
	else
		m_head->right = nnode;



	return true;
}

bool ConditionalTree::addJunction(CTokenPtr cmpOP, int pLevel)
{
	if (!cmpOP || !m_head) return false;

	auto* nnode = new CNode(cmpOP);
	m_nodes.push_back(nnode);

	if (pLevel == m_p_level)
	{
		CNode* prevHead = m_head;
		m_head = nnode;
		m_head->left = prevHead;
	}
	else
	{
		if (m_head->right)
			nnode->left = m_head->right;
		m_head->right = nnode;

		return forwardJunction(cmpOP, pLevel);
	}

	return true;
}

bool ConditionalTree::merge(int pLevel)
{
	if (!m_subTree) return true;

	if (pLevel > m_p_level)
	{
		m_subTree->merge(pLevel);
		
	}

	printf("[%d] Merging sub tree (%d).\n", m_p_level, pLevel);
	m_head->right = m_subTree->m_head;

	// Check efficneity here.
	for (int i = 0; i < m_subTree->m_nodes.size(); i++)
		m_nodes.push_back(m_subTree->m_nodes[i]);

	delete m_subTree;
	m_subTree = nullptr;

	return true;
}

void ConditionalTree::dumpTree()
{
	_int_dumpTree(m_head);
	putchar('\n');

}

bool ConditionalTree::forwardSubCondition(CTokenPtr op, CTokenPtr left, CTokenPtr right, int pLevel)
{
	if (!m_subTree)
		m_subTree = new ConditionalTree(m_p_level + 1);

	assert(m_subTree->addSubCondition(op, left, right, pLevel));
	return true;

}

bool ConditionalTree::forwardJunction(CTokenPtr cmpOP, int pLevel)
{
	if (!m_subTree)
		m_subTree = new ConditionalTree(m_p_level + 1);

	assert(m_subTree->addJunction(cmpOP, pLevel));
	return true;
}

void ConditionalTree::_int_dumpTree(const CNode* head)
{
	if (head)
	{
		putchar('(');
		printf(" %s ", kdl::getTokenName(head->value->t));
		_int_dumpTree(head->left);
		_int_dumpTree(head->right);
		putchar(')');

	}
}
