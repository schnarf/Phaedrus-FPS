/* VM/Script.h
 *
 * Virtual Machine script object. Internally corresponds to lua scripts.
 */
 
#ifndef _VM_SCRIPT_H_
#define _VM_SCRIPT_H_

namespace VM {

	class VM;
	
	class Script {
	public:
		//! Initialize from a script file
		Script( string strFilename, VM* pVM );
		
		//! Get the script's code
		const string& GetCode() const;
		
		//! Get the script's name
		const string& GetName() const { return m_strFilename; }
	private:
		string m_code;
		VM* m_pVM;
		string m_strFilename;
	}; // end class Script

}; // end namespace VM

#endif
