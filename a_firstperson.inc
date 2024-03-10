// - - - - - - - - : datas


// (C) Copyright by Y-Hypezin (R)

// @include      : a_firstperson
// @version      : ( 3 )
// @infoV        : ( 3.8.5.1 ) : discriminator.define(s).function(s).codchange(s) - note: if the information from a new update is repeated in this version, discriminator(version) ++
// @github       : https://github.com/Y-Hypezin
// @date         : 10th march 2024

// @author       : Y-Hypezin
// @contributors : -
// @sent by      : Y-Hypezin
// @codelock     : this code is open for modifications, but it is necessary to have my credits!

// @comments     : the 'streamer Plug-In' can only be used on 'OPEN.MP' servers because of the plug-in's limitations for 'SAMP' servers


// - - - - - - - - : include


// custom include-guard to ensure we don't duplicate
#if (!defined _INC_a_firstperson)
	// define the include (indentifier)
	#define _INC_a_firstperson
#else
    // for because it is already defined in another environment
    #endinput 
#endif


// - - - - - - - - : natives


/// functions

/// native ResetAllPlayerCamPos (playerid);
/// native SetPlayerFirstPersonCamPosition (Float: position, type = FP_FOOT_TYPE, mode = FP_FRONT_MODE);
/// native SetCameraFirstPerson (playerid, bool: use_in_veh = true);
/// native CancelCameraFirstPerson (playerid);
/// native IsPlayerInFirstPerson (playerid);


// - - - - - - - - : defines


#if (!defined INC_FP_OBJECT_CAM)
	#define INC_FP_OBJECT_CAM 19300
#endif


#define FP_FOOT_TYPE 0
#define FP_SWIM_TYPE 1
#define FP_CROUCH_TYPE 2
#define FP_VEH_TYPE 3 
#define FP_AIM_TYPE 4

#define FP_FRONT_MODE 0
#define FP_HEIGHT_MODE 1


// - - - - - - - - : variables


static stock 
	#if (defined _streamer_included && defined _INC_open_mp)
		STREAMER_TAG_OBJECT: _obj_cam [MAX_PLAYERS],
	#else
		_obj_cam [MAX_PLAYERS],
	#endif

	bool: _crouched_cam [MAX_PLAYERS],
	bool: _aim_cam [MAX_PLAYERS],
	bool: _in_swimming [MAX_PLAYERS],
	bool: _use_in_vehicle [MAX_PLAYERS],
	Float: _cam_f_positions [MAX_PLAYERS] [5],
	Float: _cam_h_positions [MAX_PLAYERS] [5]
;

new stock 
	bool: _in_first_cam [MAX_PLAYERS]
;


// - - - - - - - - : functions


stock ResetAllPlayerCamPos (
	playerid
) {
	// FRONT
	_cam_f_positions [playerid] [0] = 0.28; // FOOT - [ 0.28 ]
	_cam_f_positions [playerid] [1] = 0.7; // SWIM - [ 0.7 ]
	_cam_f_positions [playerid] [2] = 0.4; // CROUCH - [ 0.4 ]
	_cam_f_positions [playerid] [3] = 0.2; // VEH - [ 0.2 ]
	_cam_f_positions [playerid] [4] = 0.5; // AIM - [ 0.5 ]

	// HEIGHT
	_cam_h_positions [playerid] [0] = 0.7; // FOOT - [ 0.7 ]
	_cam_h_positions [playerid] [1] = 0.55; // SWIM - [ 0.55 ]
	_cam_h_positions [playerid] [2] = 0.07; // CROUCH - [ 0.07 ]
	_cam_h_positions [playerid] [3] = 0.7; // VEH - [ 0.7 ]
	_cam_h_positions [playerid] [4] = 0.52; // AIM - [ 0.52 ]
	return
		1
	;
}

stock SetPlayerFirstPersonCamPosition (
	playerid,
	Float: position, 
	type = FP_FOOT_TYPE,
	mode = FP_FRONT_MODE
) {
	if (!FP_FRONT_MODE)
		_cam_f_positions [playerid] [type] = position;
	else
        _cam_h_positions [playerid] [type] = position;
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
	#if (defined _streamer_included && defined _INC_open_mp)
		DestroyDynamicObject (_obj_cam [playerid]);
		_obj_cam [playerid] = CreateDynamicObject (INC_FP_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		AttachDynamicObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_FOOT_TYPE], _cam_h_positions [playerid] [FP_FOOT_TYPE], 0.0, 0.0, 0.0);
		AttachCameraToDynamicObject (playerid, _obj_cam [playerid]);
	#else
		DestroyObject (_obj_cam [playerid]);
		_obj_cam [playerid] = CreateObject (INC_FP_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_FOOT_TYPE], _cam_h_positions [playerid] [FP_FOOT_TYPE], 0.0, 0.0, 0.0);
		AttachCameraToObject (playerid, _obj_cam [playerid]);
	#endif
	return 
		1
	;
}

stock CancelCameraFirstPerson (
	playerid
) {
	_in_first_cam [playerid] = false;
	#if (defined _streamer_included && defined _INC_open_mp)
		DestroyDynamicObject (_obj_cam [playerid]);
	#else
		DestroyObject (_obj_cam [playerid]);
	#endif
	return 
		1
	;
}

#define IsPlayerInFirstPerson(%0) _in_first_cam [%0]


// - - - - - - - - : hookbacks


public OnGameModeInit (

) {
    print ("                                                                                   ");
    print (" Loading include: a_firstperson.inc                                                ");
    print ("                                                                                   ");
    print ("- - - - - - - - - - :                                                              ");
    print ("                                                                                   ");
    print ("   (C) Copyright by Y-Hypezin (R)                                                  ");
    print ("                                                                                   ");
    print ("    @include      : a_firstperson                                                  ");
    print ("    @version      : ( 3 )                                                          ");
    print ("    @infoV        : ( 3.8.5.1 )                                                    ");
    print ("    @date         : 10th march 2024                                                ");
    print ("                                                                                   ");
    print ("    @author       : Y-Hypezin                                                      ");
    print ("    @contributors : -                                                              ");
    print ("    @sent by      : Y-Hypezin                                                      ");
    print ("    @team         : Hyped                                                          ");
    print ("                                                                                   ");
    print ("- - - - - - - - - - :                                                              ");
    print ("                                                                                   ");
    print (" >> a_firstperson included v.3 (3.8.5.1)                                           ");
    print (" Loaded.                                                                           ");
    print ("                                                                                   ");

    #if (defined __OnGameModeInit_a_fp)
        return 
            __OnGameModeInit_a_fp (

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
	ResetAllPlayerCamPos (playerid);

	_in_first_cam [playerid] = false;
	_use_in_vehicle [playerid] = false;
	_crouched_cam [playerid] = false;
	_aim_cam [playerid] = false;
	_in_swimming [playerid] = false;
    #if (defined __OnPlayerConnect_a_fp)
        return 
            __OnPlayerConnect_a_fp (
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
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachCameraToDynamicObject (playerid, _obj_cam [playerid]);
			#else
				AttachCameraToObject (playerid, _obj_cam [playerid]);
			#endif
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
    #if (defined __OnPlayerSpawn_a_fp)
        return 
            __OnPlayerSpawn_a_fp (
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
		#if (defined _streamer_included && defined _INC_open_mp)
			DestroyDynamicObject (_obj_cam [playerid]);
			_obj_cam [playerid] = CreateDynamicObject (INC_FP_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			AttachDynamicObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_VEH_TYPE], _cam_h_positions [playerid] [FP_VEH_TYPE], 0.0, 0.0, 0.0);
			AttachCameraToDynamicObject (playerid, _obj_cam [playerid]);
		#else
			DestroyObject (_obj_cam [playerid]);
			_obj_cam [playerid] = CreateObject (INC_FP_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_VEH_TYPE], _cam_h_positions [playerid] [FP_VEH_TYPE], 0.0, 0.0, 0.0);
			AttachCameraToObject (playerid, _obj_cam [playerid]);
		#endif
	} else if (IsPlayerInFirstPerson (playerid)) {
		#if (defined _streamer_included && defined _INC_open_mp)
			DestroyDynamicObject (_obj_cam [playerid]);
		#else
			DestroyObject (_obj_cam [playerid]);
		#endif
		SetCameraBehindPlayer (playerid);
	}
	#if (defined __OnPlayerEnterVehicle_a_fp)
        return 
            __OnPlayerEnterVehicle_a_fp (
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
	#if (defined __OnPlayerExitVehicle_a_fp)
        return 
            __OnPlayerExitVehicle_a_fp (
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
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachDynamicObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_AIM_TYPE], _cam_h_positions [playerid] [FP_AIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _obj_cam [playerid]);
			#else
				AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_AIM_TYPE], _cam_h_positions [playerid] [FP_AIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _obj_cam [playerid]); 
			#endif
		} else if ((newkeys & (KEY_SPRINT)) && (!strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_in_swimming [playerid] = true;
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachDynamicObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_SWIM_TYPE], _cam_h_positions [playerid] [FP_SWIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _obj_cam [playerid]);
			#else
				AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_SWIM_TYPE], _cam_h_positions [playerid] [FP_SWIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _obj_cam [playerid]); 
			#endif
		} else if ((newkeys & (KEY_UP)) && (!strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_in_swimming [playerid] = true;
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachDynamicObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_SWIM_TYPE], _cam_h_positions [playerid] [FP_SWIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _obj_cam [playerid]);
			#else
				AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_SWIM_TYPE], _cam_h_positions [playerid] [FP_SWIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _obj_cam [playerid]); 
			#endif
		} else if((((newkeys & (KEY_SPRINT)) != (KEY_SPRINT)) && ((oldkeys & (KEY_SPRINT)) == (KEY_SPRINT))) && (!strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_in_swimming [playerid] = false;
			SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
		} else if((((newkeys & (KEY_UP)) != (KEY_UP)) && ((oldkeys & (KEY_UP)) == (KEY_UP))) && (!strcmp (_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_in_swimming [playerid] = false;
			SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
		}
	}
	#if (defined __OnPlayerKeyStateChange_a_fp)
        return 
            __OnPlayerKeyStateChange_a_fp (
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
		if ((((anim >= 1160) && (anim <= 1163)) || (anim == 1167) || (anim == 1365) || (anim == 1643) || (anim == 1453) || (anim == 220)) && GetPlayerSpecialAction (playerid) != SPECIAL_ACTION_DUCK) {
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachDynamicObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_AIM_TYPE], _cam_h_positions [playerid] [FP_AIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _obj_cam [playerid]);
			#else
				AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_AIM_TYPE], _cam_h_positions [playerid] [FP_AIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _obj_cam [playerid]);
			#endif
		} else if (GetPlayerCameraMode (playerid) != 46 && _aim_cam [playerid]) {
			_aim_cam [playerid] = false;
			if (!_crouched_cam [playerid]) {
				SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
			} else {
				#if (defined _streamer_included && defined _INC_open_mp)
					DestroyDynamicObject (_obj_cam [playerid]);
					_obj_cam [playerid] = CreateDynamicObject (INC_FP_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
					AttachDynamicObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_CROUCH_TYPE], _cam_h_positions [playerid] [FP_CROUCH_TYPE], 0.0, 0.0, 0.0);
					AttachCameraToDynamicObject (playerid, _obj_cam [playerid]);
				#else
					DestroyObject (_obj_cam [playerid]);
					_obj_cam [playerid] = CreateObject (INC_FP_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
					AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_CROUCH_TYPE], _cam_h_positions [playerid] [FP_CROUCH_TYPE], 0.0, 0.0, 0.0);
					AttachCameraToObject (playerid, _obj_cam [playerid]);
				#endif
			}
		} else if (GetPlayerSpecialAction (playerid) != SPECIAL_ACTION_DUCK && _crouched_cam [playerid]) {
			_crouched_cam [playerid] = false;
			SetCameraFirstPerson (playerid, _use_in_vehicle [playerid]);
			//AttachCameraToObject (playerid, _obj_cam [playerid]);
		} else if (GetPlayerSpecialAction (playerid) == SPECIAL_ACTION_DUCK && !_crouched_cam [playerid]) {
			#if (defined _streamer_included && defined _INC_open_mp)
				DestroyDynamicObject (_obj_cam [playerid]);
				_obj_cam [playerid] = CreateDynamicObject (INC_FP_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_CROUCH_TYPE], _cam_h_positions [playerid] [FP_CROUCH_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _obj_cam [playerid]);
			#else
				DestroyObject (_obj_cam [playerid]);
				_obj_cam [playerid] = CreateObject (INC_FP_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
				AttachObjectToPlayer (_obj_cam [playerid], playerid, 0.0, _cam_f_positions [playerid] [FP_CROUCH_TYPE], _cam_h_positions [playerid] [FP_CROUCH_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _obj_cam [playerid]);
			#endif
			_crouched_cam [playerid] = true;
		} 
	}
    #if (defined __OnPlayerUpdate_a_fp)
        return 
            __OnPlayerUpdate_a_fp (
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


#define OnGameModeInit __OnGameModeInit_a_fp

#define OnPlayerConnect __OnPlayerConnect_a_fp

#define OnPlayerSpawn __OnPlayerSpawn_a_fp

#define OnPlayerEnterVehicle __OnPlayerEnterVehicle_a_fp

#define OnPlayerExitVehicle __OnPlayerExitVehicle_a_fp

#define OnPlayerKeyStateChange __OnPlayerKeyStateChange_a_fp

#define OnPlayerUpdate __OnPlayerUpdate_a_fp

// - - - - - - - - : + + +


#if (defined __OnGameModeInit_a_fp)
	forward __OnGameModeInit_a_fp (

    );
#endif

#if (defined __OnPlayerConnect_a_fp)
	forward __OnPlayerConnect_a_fp (
        playerid
    );
#endif


#if (defined __OnPlayerSpawn_a_fp)
	forward  __OnPlayerSpawn_a_fp (
		playerid
	);
#endif

#if (defined __OnPlayerEnterVehicle_a_fp)
	forward __OnPlayerEnterVehicle_a_fp (
		playerid, 
		vehicleid,
		ispassenger
	);
#endif

#if (defined __OnPlayerExitVehicle_a_fp)
	forward __OnPlayerExitVehicle_a_fp (
		playerid, 
		vehicleid
	);
#endif

#if (defined __OnPlayerKeyStateChange_a_fp)
	forward __OnPlayerKeyStateChange_a_fp (
		playerid, 
		newkeys, 
		oldkeys
	);
#endif

#if (defined __OnPlayerUpdate_a_fp)
	forward __OnPlayerUpdate_a_fp (
        playerid
    );
#endif

// - - - - - - - - : end
