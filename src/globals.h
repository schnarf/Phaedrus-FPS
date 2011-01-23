/* globasl.h
 *
 * Externs for any engine globals
 */

#pragma once

namespace World { class ResourceManager; }
namespace VM { class VM; }
namespace System { class VFS; class Input; }

extern System::VFS* g_pVFS;
extern World::ResourceManager* g_pResourceManager;
extern VM::VM* g_pVM;
extern System::Input* g_pInput;