/*
* Copyright (C) 2025 Nathan Handley <https://github.com/NathanHandley/>
* Copyright (C) 2018 AzerothCore <http://www.azerothcore.org>
* Copyright (C) 2012 CVMagic <http://www.trinitycore.org/f/topic/6551-vas-autobalance/>
* Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* Copyright (C) 1985-2010 KalCorp  <http://vasserver.dyndns.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/*
* Script Name: DungeonScale
* Rewrite into DungeonScale: Nathan Handley (https://github.com/NathanHandley/mod-dungeon-scale)
* Original Script Name: AutoBalance
* AutoBalance Original Authors: KalCorp and Vaughner
* Original Maintainer(s): AzerothCore
* Description: Allows changing dungeon scaling per number of players
*/

#ifndef MOD_DUNGEONSCALE_H
#define MOD_DUNGEONSCALE_H

#include "ScriptMgr.h"
#include "Creature.h"

// Manages registration, loading, and execution of scripts.
class DungeonScaleScriptMgr
{
    public: /* Initialization */

        static DungeonScaleScriptMgr* instance();
        // called at the start of ModifyCreatureAttributes method
        // it can be used to add some condition to skip autobalancing system for example
        bool OnBeforeModifyAttributes(Creature* creature, uint32 & instancePlayerCount);
        // called right after default multiplier has been set, you can use it to change
        // current scaling formula based on number of players or just skip modifications
        bool OnAfterDefaultMultiplier(Creature* creature, float &defaultMultiplier);
        // called before change creature values, to tune some values or skip modifications
        bool OnBeforeUpdateStats(Creature* creature, uint32 &scaledHealth, uint32 &scaledMana, float &damageMultiplier, uint32 &newBaseArmor);
};

#define sDSScriptMgr DungeonScaleScriptMgr::instance()

/*
* Dedicated hooks for Autobalance Module
* Can be used to extend/customize this system
*/
class DungeonScaleModuleScript : public ModuleScript
{
    protected:

        DungeonScaleModuleScript(const char* name);

    public:
        virtual bool OnBeforeModifyAttributes(Creature* /*creature*/, uint32 & /*instancePlayerCount*/) { return true; }
        virtual bool OnAfterDefaultMultiplier(Creature* /*creature*/, float & /*defaultMultiplier*/) { return true; }
        virtual bool OnBeforeUpdateStats(Creature* /*creature*/, uint32 &/*scaledHealth*/, uint32 &/*scaledMana*/, float &/*damageMultiplier*/, uint32 &/*newBaseArmor*/) { return true; }
};

template class ScriptRegistry<DungeonScaleModuleScript>;

#endif
