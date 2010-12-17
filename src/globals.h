/* globasl.h
 *
 * Externs for any engine globals
 */

#pragma once

namespace System { class VFS; }
namespace World { class ResourceManager; }
namespace VM { class VM; }
namespace System { class Kernel; }

extern System::VFS* g_pVFS;
extern World::ResourceManager* g_pResourceManager;
extern VM::VM* g_pVM;