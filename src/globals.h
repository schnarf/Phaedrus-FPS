/* globasl.h
 *
 * Externs for any engine globals
 */

#pragma once

namespace System { class VFS; }
namespace World { class ResourceManager; }
namespace VM { class VM; }

extern System::VFS g_VFS;
extern World::ResourceManager g_ResourceManager;
extern VM::VM g_VM;