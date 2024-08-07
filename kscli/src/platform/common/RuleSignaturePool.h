#ifndef PLATFORM_COMMON_RULE_SIGNATURE_POOL_H_
#define PLATFORM_COMMON_RULE_SIGNATURE_POOL_H_

#include <libdetutil/kdl/kdl.h>
#include <unordered_map>
#include <string>
namespace kscli
{

class RuleSignaturePool
{
public:

	inline 
	void addRule(const std::string& str, LDU_FILE_DETECTION_FN fn)
	{
		m_detectors[str] = fn;
	}

private:

	std::unordered_map<
		std::string, 
		LDU_FILE_DETECTION_FN
	> m_detectors;


};

} // kscli


#endif // PLATFORM_COMMON_RULE_SIGNATURE_POOL_H_