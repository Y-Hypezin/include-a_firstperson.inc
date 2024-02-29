// - - - - - - - - : datas


// (C) Copyright by zHypezinXzL(R)

// @include      : a_first_person
// @version      : ( 1 )
// @infoV        : ( 1.10.4.3.1 ) : discriminator.define(s).function(s).improvedcodes.codchange(s) - note: if the information from a new update is repeated in this version, discriminator(version) ++
// @github       : https://github.com/zHypezinXzL
// @date         : 29th feb. 2024

// @author       : zHypezinXzL
// @contributors : -
// @sent by      : zHypezinXzL
// @codelock     : this code is open for modifications, but it is necessary to have my credits!

// @comments     : -


// - - - - - - - - : include


// custom include-guard to ensure we don't duplicate
#if (defined _INC_a_first_person)
    // for because it is already defined in another environment
    #endinput 
#endif

// define the include (indentifier)
#define _INC_a_first_person

// Port to open.mp and loads default variables as INVALID_PLAYER_TEXT_DRAW. (If they are using samp-stdlib)
#tryinclude <open.mp>

#if (!defined _INC_open_mp)
    #tryinclude <a_samp>
#endif


// - - - - - - - - : natives


/// functions

/// native SetFirstPersonCamPosition (Float: position, type = FC_FOOT_TYPE, mode = FC_FRONT_MODE);
/// native SetCameraFirstPerson (playerid, bool: use_in_veh = true);
/// native CancelCameraFirstPerson (playerid);
/// native IsPlayerInFirstPerson (playerid);


// - - - - - - - - : defines


#define FC_CREATE_OBJ CreateObject
#if (defined _streamer_included)
	#define FC_CREATE_OBJ CreateDynamicObject
#endif

#define FC_DESTROY_OBJ DestroyObject
#if (defined _streamer_included)
	#define FC_DESTROY_OBJ DestroyDynamicObject
#endif

#if (!defined INC_FC_OBEJECT_CAM)
	#define INC_FC_OBEJECT_CAM 19300
#endif

enum {
	FC_FOOT_TYPE,
	FC_SWIM_TYPE,
	FC_CROUCH_TYPE,
	FC_VEH_TYPE,
	FC_AIM_TYPE
};

enum {
	FC_FRONT_MODE = 1,
	FC_HEIGHT_MODE = 2
};


// - - - - - - - - : variables


static stock 
	#if (defined _streamer_included)
		STREAMER_TAG_OBJECT: _obj_cam [MAX_PLAYERS],
	#else
		_obj_cam [MAX_PLAYERS],
	#endif

	bool: _crouched_cam [MAX_PLAYERS],
	bool: _aim_cam [MAX_PLAYERS],
	bool: _in_swimming [MAX_PLAYERS],
	bool: _use_in_vehicle [MAX_PLAYERS],
	Float: _cam_positions [10] = {
		// FRONT
		Float: 0.28, // FOOT - [ 0.25 ]
		Float: 0.7, // SWIM - [ 0.7 ]
		Float: 0.4, // CROUCH - [ 0.3 ]
		Float: 0.2, // VEH - [ -0.2 ]
		Float: 0.5, // AIM - [ -0.1 ]

		// HEIGHT
		Float: 0.7, // FOOT - [ 0.7 ]
		Float: 0.55, // SWIM - [ 0.55 ]
		Float: 0.07, // CROUCH - [ 0.15 ]
		Float: 0.7, // VEH - [ 0.55 ]
		Float: 0.52 // AIM - [ 0.85 ]
	}
;

new stock 
	bool: _in_first_cam [MAX_PLAYERS]
;


// - - - - - - - - : functions


stock SetFirstPersonCamPosition (
	Float: position, 
	type = FC_FOOT_TYPE,
	mode = FC_FRONT_MODE
) {
	_cam_positions [type + ((mode == 2) ? (5) : (0))] = position;
	return 
		1
	;
}

stock SetCameraFirstPerson (
	playerid,
	bool: use_in_veh = true
) {
	_in_first_cam [playerid] = true;
	_use_in_vehicle [playerid] = use_in_veh;

	FC_DESTROY_OBJ (_obj_cam [playerid]);
	_obj_cam [playerid] = FC_CREATE_OBJ (INC_FC_OBEJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_positions [FC_FOOT_TYPE], _cam_positions [FC_FOOT_TYPE + 5], 0.0, 0.0, 0.0);
 	AttachCameraToObject (playerid, _obj_cam [playerid]);
	return 
		1
	;
}

stock CancelCameraFirstPerson (
	playerid
) {
	_in_first_cam [playerid] = false;
	FC_DESTROY_OBJ (_obj_cam [playerid]);
	return 
		1
	;
}

#define IsPlayerInFirstPerson(%0) _in_first_cam [%0]


// - - - - - - - - : hookbacks


public OnGameModeInit (

) {
    print ("                                                                                   ");
    print (" Loading include: a_first_person.inc                                               ");
    print ("                                                                                   ");
    print ("- - - - - - - - - - :                                                              ");
    print ("                                                                                   ");
    print ("   (C) Copyright by zHypezinXzL (R)                                                ");
    print ("                                                                                   ");
    print ("    @include      : a_first_person                                                 ");
    print ("    @version      : ( 1 )                                                          ");
    print ("    @infoV        : ( 1.10.4.3.1 )                                                 ");
    print ("    @date         : 29th feb. 2024                                                 ");
    print ("                                                                                   ");
    print ("    @author       : zHypezinXzL                                                    ");
    print ("    @contributors : -                                                              ");
    print ("    @sent by      : zHypezinXzL                                                    ");
    print ("    @team         : Hyped                                                          ");
    print ("                                                                                   ");
    print ("- - - - - - - - - - :                                                              ");
    print ("                                                                                   ");
    print (" >> a_first_person included v.1 (1.10.4.3.1)                                       ");
    print (" Loaded.                                                                           ");
    print ("                                                                                   ");

    #if (defined __OnGameModeInit_a_fc)
        return 
            __OnGameModeInit_a_fc (

            )
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerConnect (
	playerid
) {
	_in_first_cam [playerid] = false;
	_use_in_vehicle [playerid] = false;
	_crouched_cam [playerid] = false;
	_aim_cam [playerid] = false;
	_in_swimming [playerid] = false;
    #if (defined __OnPlayerConnect_a_fc)
        return 
            __OnPlayerConnect_a_fc (
				playerid
            )
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerSpawn (
	playerid
) {
	if (IsPlayerInFirstPerson (playerid)) {

		new 
			anim = GetPlayerAnimationIndex (playerid)
		;
		if (!(((anim >= 1160) && (anim <= 1163)) || (anim == 1167) || (anim == 1365) || (anim == 1643) || (anim == 1453) || (anim == 220))) {
			SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
		}

		//////////////////

		if (GetPlayerSpecialAction (playerid) != SPECIAL_ACTION_DUCK && !IsPlayerInAnyVehicle (playerid)) {
			AttachCameraToObject (playerid, _obj_cam [playerid]);
		}

		//////////////////

		static
			_animlib [2] [32] = {0, ...}
		;
		GetAnimationName (GetPlayerAnimationIndex (playerid), _animlib [0], 32, _animlib [1], 32);
		if (!(!strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid)) && _in_swimming  [playerid]) {
			SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
			_in_swimming [playerid] = false;
		}
	}
    #if (defined __OnPlayerSpawn_a_fc)
        return 
            __OnPlayerSpawn_a_fc (
				playerid
            )
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerEnterVehicle (
	playerid, 
	vehicleid, 
	ispassenger
) {
	if (IsPlayerInFirstPerson (playerid) && _use_in_vehicle [playerid]) {
		FC_DESTROY_OBJ (_obj_cam [playerid]);
		_obj_cam [playerid] = FC_CREATE_OBJ (INC_FC_OBEJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		//SetCameraBehindPlayer (playerid);
		AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_positions [FC_VEH_TYPE], _cam_positions [FC_VEH_TYPE + 5], 0.0, 0.0, 0.0);
		AttachCameraToObject (playerid, _obj_cam [playerid]);
	} else if (IsPlayerInFirstPerson (playerid)) {
		FC_DESTROY_OBJ (_obj_cam [playerid]);
		SetCameraBehindPlayer (playerid);
	}
	#if (defined __OnPlayerEnterVehicle_a_fc)
        return 
            __OnPlayerEnterVehicle_a_fc (
				playerid, 
				vehicleid,
				ispassenger
			)
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerExitVehicle (
	playerid, 
	vehicleid
) {
	if (IsPlayerInFirstPerson (playerid)) {
		SetCameraFirstPerson(playerid, _use_in_vehicle [playerid]);
	}
	#if (defined __OnPlayerExitVehicle_a_fc)
        return 
            __OnPlayerExitVehicle_a_fc (
				playerid, 
				vehicleid
			)
        ;
    #else 
        return 
            1
        ;
    #endif
}


public OnPlayerKeyStateChange (
	playerid, 
	newkeys, 
	oldkeys
) {
	if (IsPlayerInFirstPerson (playerid)) {
		static
			_animlib [2] [32] = {0, ...}
		;
		GetAnimationName (GetPlayerAnimationIndex (playerid), _animlib [0], 32, _animlib [1], 32);
		if ((newkeys & (KEY_HANDBRAKE | KEY_FIRE)) && strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid)) {
			_aim_cam [playerid] = true;
			AttachObjectToPlayer(_obj_cam [playerid], playerid, 0.0, _cam_positions [FC_AIM_TYPE], _cam_positions [FC_AIM_TYPE + 5], 0.0, 0.0, 0.0);
			AttachCameraToObject(playerid, _obj_cam [playerid]); 
		} else if ((newkeys & (KEY_SPRINT)) && (!strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_in_swimming [playerid] = true;
			AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_positions [FC_SWIM_TYPE], _cam_positions [FC_SWIM_TYPE + 5], 0.0, 0.0, 0.0);
			AttachCameraToObject (playerid, _obj_cam [playerid]);
		} else if ((newkeys & (KEY_UP)) && (!strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_in_swimming [playerid] = true;
			AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_positions [FC_SWIM_TYPE], _cam_positions [FC_SWIM_TYPE + 5], 0.0, 0.0, 0.0);
			AttachCameraToObject (playerid, _obj_cam [playerid]);
		} else if((((newkeys & (KEY_SPRINT)) != (KEY_SPRINT)) && ((oldkeys & (KEY_SPRINT)) == (KEY_SPRINT))) && (!strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_in_swimming [playerid] = false;
			SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
		} else if((((newkeys & (KEY_UP)) != (KEY_UP)) && ((oldkeys & (KEY_UP)) == (KEY_UP))) && (!strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_in_swimming [playerid] = false;
			SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
		}
	}
	#if (defined __OnPlayerKeyStateChange_a_fc)
        return 
            __OnPlayerKeyStateChange_a_fc (
				playerid, 
				newkeys, 
				oldkeys
			)
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerUpdate (
	playerid
) {
	if (IsPlayerInFirstPerson (playerid)) {
		new 
			anim = GetPlayerAnimationIndex (playerid)
		;
		AttachCameraToObject (playerid, _obj_cam [playerid]);
		if ((((anim >= 1160) && (anim <= 1163)) || (anim == 1167) || (anim == 1365) || (anim == 1643) || (anim == 1453) || (anim == 220)) && GetPlayerSpecialAction (playerid) != SPECIAL_ACTION_DUCK) {
			AttachObjectToPlayer(_obj_cam [playerid], playerid, 0.0, _cam_positions [FC_AIM_TYPE], _cam_positions [FC_AIM_TYPE + 5], 0.0, 0.0, 0.0);
			AttachCameraToObject(playerid, _obj_cam [playerid]); 
		} else if (GetPlayerCameraMode (playerid) != 46 && _aim_cam [playerid]) {
			_aim_cam [playerid] = false;
			if (!_crouched_cam [playerid]) {
				SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
			} else {
				FC_DESTROY_OBJ (_obj_cam [playerid]);
				_obj_cam [playerid] = FC_CREATE_OBJ (INC_FC_OBEJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
				AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_positions [FC_CROUCH_TYPE], _cam_positions [FC_CROUCH_TYPE + 5], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _obj_cam [playerid]);
			}
		} else if (GetPlayerSpecialAction (playerid) != SPECIAL_ACTION_DUCK && _crouched_cam [playerid]) {
			_crouched_cam [playerid] = false;
			SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
			//AttachCameraToObject (playerid, _obj_cam [playerid]);
		} else if (GetPlayerSpecialAction (playerid) == SPECIAL_ACTION_DUCK && !_crouched_cam [playerid]) {
			FC_DESTROY_OBJ (_obj_cam [playerid]);
			_obj_cam [playerid] = FC_CREATE_OBJ (INC_FC_OBEJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_positions [FC_CROUCH_TYPE], _cam_positions [FC_CROUCH_TYPE + 5], 0.0, 0.0, 0.0);
			AttachCameraToObject (playerid, _obj_cam [playerid]);
			_crouched_cam [playerid] = true;
		} 
	}
    #if (defined __OnPlayerUpdate_a_fc)
        return 
            __OnPlayerUpdate_a_fc (
				playerid
            )
        ;
    #else 
        return 
            1
        ;
    #endif
}


// - - - - - - - - : hooks 


#if (defined _ALS_OnGameModeInit)
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#if (defined _ALS_OnPlayerConnect)
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#if (defined _ALS_OnPlayerSpawn)
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif

#if (defined _ALS_OnPlayerEnterVehicle)
    #undef OnPlayerEnterVehicle
#else
    #define _ALS_OnPlayerEnterVehicle
#endif

#if (defined _ALS_OnPlayerExitVehicle)
    #undef OnPlayerExitVehicle
#else
    #define _ALS_OnPlayerExitVehicle
#endif

#if (defined _ALS_OnPlayerKeyStateChange)
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif

#if (defined _ALS_OnPlayerUpdate)
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif

// - - - - - - - - : + + +


#define OnGameModeInit __OnGameModeInit_a_fc

#define OnPlayerConnect __OnPlayerConnect_a_fc

#define OnPlayerSpawn __OnPlayerSpawn_a_fc

#define OnPlayerEnterVehicle __OnPlayerEnterVehicle_a_fc

#define OnPlayerExitVehicle __OnPlayerExitVehicle_a_fc

#define OnPlayerKeyStateChange __OnPlayerKeyStateChange_a_fc

#define OnPlayerUpdate __OnPlayerUpdate_a_fc

// - - - - - - - - : + + +


#if (defined __OnGameModeInit_a_fc)
	forward __OnGameModeInit_a_fc (

    );
#endif

#if (defined __OnPlayerConnect_a_fc)
	forward __OnPlayerConnect_a_fc (
        playerid
    );
#endif


#if (defined __OnPlayerSpawn_a_fc)
	forward  __OnPlayerSpawn_a_fc (
		playerid
	);
#endif

#if (defined __OnPlayerEnterVehicle_a_fc)
	forward __OnPlayerEnterVehicle_a_fc (
		playerid, 
		vehicleid,
		ispassenger
	);
#endif

#if (defined __OnPlayerExitVehicle_a_fc)
	forward __OnPlayerExitVehicle_a_fc (
		playerid, 
		vehicleid
	);
#endif

#if (defined __OnPlayerKeyStateChange_a_fc)
	forward __OnPlayerKeyStateChange_a_fc (
		playerid, 
		newkeys, 
		oldkeys
	);
#endif

#if (defined __OnPlayerUpdate_a_fc)
	forward __OnPlayerUpdate_a_fc (
        playerid
    );
#endif


// - - - - - - - - : end
