#include "parser/RuleParser.h"

using kdl::RuleParser;
using kdl::CTokenMapIter;
using kdl::token_t;
using kdl::Token;
using kdl::CTokenPtr;


constexpr static bool nextTokenIsSection(token_t t)
{
	return (t >= token_t::SI_META && t <= token_t::SI_CONDITIONS);
}

RuleParser::RuleParser(CTokenMapView& tokenView, Rule& newRule)
	: m_rule(newRule),
	  m_tokenMapView(tokenView), 
	  m_numTokens(tokenView.size()),
	  m_currentState(NO_SECTION)
{
	m_cursor = 0;
}

bool RuleParser::parse()
{
	if(!parseHeader())
		return false;

	while (!isAtEnd())
	{
		if (!parseSection()) return false;
	}

	return true;
}

CTokenPtr RuleParser::advance()
{
	return &m_tokenMapView[m_cursor++];
}

inline bool RuleParser::isAtEnd()
{
	return m_cursor >= m_numTokens;
}

CTokenPtr RuleParser::peek()
{
	if (isAtEnd()) return nullptr;
	return &m_tokenMapView[m_cursor];
}

CTokenPtr RuleParser::previous()
{
	if (m_cursor == 0) return nullptr;

	return &m_tokenMapView[m_cursor - 1];
}

bool RuleParser::check(token_t t)
{
	if (isAtEnd()) return false;
	return peek()->t == t;
}

bool RuleParser::parseHeader()
{
	if (matchInOrder({ token_t::SI_RULES, token_t::IDENTIFIER }))
	{
		printf("Found new rule: %s\n", m_tokenMapView[1].val.c_str());
		
		m_rule.setName(m_tokenMapView[1].val.c_str());

		if (peek()->t == token_t::COLON)
		{
			advance();
			if (peek()->t != token_t::IDENTIFIER)
			{
				printf("error\n");
				return false;
			}
			else
			{
				printf("Paramter found: %s\n", peek()->val.c_str());
				
				m_rule.setRuleParameters(peek()->val);
			}
			// get past the param id
			advance();
		}

		else if (peek()->t == token_t::OPEN_BRACE)
			printf("Rule has no paramters\n");
		
		// get past the open brace
		advance();

		return true;
	}

	return false;

}

bool RuleParser::parseSection()
{
	auto* next = peek();
	if (nextTokenIsSection(next->t))
	{
		advance();
		if (peek()->t != token_t::COLON)
		{
			printf("error\n");
			return false;
		}

		advance();
	
		switch (next->t)
		{
			case token_t::SI_CONTENT:
				return parseVariables();
			default:
				abort();
		}
	}

	return false;

}

bool RuleParser::parseVariables()
{
	printf("Parsing variables\n");

	while (!(nextTokenIsSection(peek()->t)))
	{
		if ( !( matchInOrder( { token_t::TI_VARIABLE, token_t::IDENTIFIER, token_t::ASSIGNMENT } ) ) )
		{
			printf("invalid\n");
			return false;
		}
		Variable::Type tType;


		switch (peek()->t)
		{
			case token_t::STRING:
				tType = Variable::STRING;
				break;
			case token_t::REGEXP:
				tType = Variable::REGEX;
				break;
			case token_t::BYTE_SEQ:
				tType = Variable::BYTE_SEQUENCE;
				break;
			default:
				printf("Invalid expression\n");
				return false;
		}


		const std::string& name = m_tokenMapView[m_cursor - 2].val;



		advance();

		printf("Found variable: %s with '%s' as value\n", 
			m_tokenMapView[m_cursor-3].val.c_str(), 
			m_tokenMapView[m_cursor-1].val.c_str());
	
	}

	return false;
}

bool RuleParser::formatVariable(Variable::Type type, std::string& value)
{
	switch (type)
	{
		case Variable::BYTE_SEQUENCE:
			return formatByteSequence(value);
		case Variable::REGEX:
			return false;
		default:
			return true;
	}
}

bool RuleParser::formatByteSequence(std::string& value)
{
	return false;
}
