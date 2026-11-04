#ifndef _Eon_Core_Core_h_
#define _Eon_Core_Core_h_

#include <Core/Core.h>
#include <Core/Ext/Ext.h>
#include <Core/MediaFormats/Audio.h>
#include <Vfs/Core/Core.h>

#if __has_include(<Geometry/Geometry.h>)
#include <Geometry/Geometry.h>
#endif

// PacketRouter must come before Ecs.h for complete type
#include "PacketRouter.h"

#include <Ecs/Ecs.h>

NAMESPACE_UPP

// Core building blocks for atoms/links and helpers
#include "Types.h"
#include "Container.h"
#include "Atom.h"
#include "LinkUtil.h"
#include "LinkBase.h"
#include "Base.h"
#include "BaseAudio.h"
#include "BaseVideo.h"
#include "Network.h"
#include "LinkFactory.h"
#include "Context.h"
#include "RouterNetContext.h"

END_UPP_NAMESPACE

#endif
