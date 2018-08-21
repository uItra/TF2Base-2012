#pragma once

enum tfweapon_t
{
	WEAPON_BAT,
	WEAPON_BOTTLE,
	WEAPON_FIREAXE,
	WEAPON_KUKRI,
	WEAPON_KNIFE,
	WEAPON_FISTS,
	WEAPON_WRENCH,
	WEAPON_BONESAW,
	WEAPON_SHOTGUN_ENGINEER,
	WEAPON_SHOTGUN_SOLDIER,
	WEAPON_SHOTGUN_HEAVY,
	WEAPON_SHOTGUN_PYRO,
	WEAPON_SCATTERGUN,
	WEAPON_SNIPERRIFLE,
	WEAPON_MINIGUN,
	WEAPON_SMG,
	WEAPON_SYRINGEGUN,
	WEAPON_ROCKETLAUNCHER,
	WEAPON_GRENADELAUNCHER,
	WEAPON_STICKYBOMBLAUNCHER,
	WEAPON_FLAMETHROWER,
	WEAPON_PISTOL_ENGINEER,
	WEAPON_PISTOL_SCOUT,
	WEAPON_REVOLVER,
	WEAPON_MEDIGUN = 29,
	WEAPON_KRITZKRIEG = 35,
	WEAPON_BLUTSAUGER,
	WEAPON_UBERSAW,
	WEAPON_AXTINGUISHER,
	WEAPON_FLAREGUN,
	WEAPON_BACKBURNER,
	WEAPON_NATSCHA,
	WEAPON_SANVICH,
	WEAPON_KGB,
	WEAPON_SANDMAN,
	WEAPON_FAN,
	WEAPON_BONK,
	WEAPON_HUNTSMAN = 56,
	WEAPON_RAZORBACK,
	WEAPON_JARATE,
	WEAPON_AMBASSADOR = 61,
	WEAPON_DIRECTHIT = 127,
	WEAPON_EQUALIZER,
	WEAPON_BUFFBANNER,
	WEAPON_SCOTTISHRESISTANCE,
	WEAPON_CHARGINTARGE,
	WEAPON_EYELANDER,
	WEAPON_GUNBOATS,
	WEAPON_WRANGLER = 140,
	WEAPON_FRONTIERJUSTICE,
	WEAPON_GUNSLINGER,
	WEAPON_HOMEWRECKER = 153,
	WEAPON_PAINTRAIN,
	WEAPON_SOUTHERNHOSPITALITY,
	WEAPON_DALOKOHS = 159,
	WEAPON_LUGERMORPH,
	WEAPON_BIGKILL,
	WEAPON_CRITACOLA,
	WEAPON_GOLDENWRENCH = 169,
	WEAPON_TRIBALMANSHIV = 171,
	WEAPON_SCOTSMANSKULLTUTTER,
	WEAPON_VITASAW,
	WEAPON_NEWBAT = 190,
	WEAPON_NEWBOTTLE,
	WEAPON_NEWFIREAXE,
	WEAPON_NEWKUKRI,
	WEAPON_NEWKNIFE,
	WEAPON_NEWFISTS,
	WEAPON_NEWSHOVEL,
	WEAPON_NEWWRENCH,
	WEAPON_NEWBONESAW,
	WEAPON_NEWSHOTGUN,
	WEAPON_NEWSCATTERGUN,
	WEAPON_NEWSNIPERRIFLE,
	WEAPON_NEWMINIGUN,
	WEAPON_NEWSMG,
	WEAPON_NEWSYRINGEGUN,
	WEAPON_NEWROCKETLAUNCHER,
	WEAPON_NEWGRENADELAUNCHER,
	WEAPON_NEWSTICKYBOMBLAUNCHER,
	WEAPON_NEWFLAMETHROWER,
	WEAPON_NEWPISTOL,
	WEAPON_NEWREVOLVER,
	WEAPON_NEWMEDIGUN,
	WEAPON_POWERJACK = 214,
	WEAPON_DEGREASER,
	WEAPON_SHORTSTOP = 220,
	WEAPON_HOLYMACKREL,
	WEAPON_MADMILK,
	WEAPON_LETRANGER = 224,
	WEAPON_ETERNALREWARD,
	WEAPON_BATTALIONBACKUP,
	WEAPON_BLACKBOX = 228,
	WEAPON_SYDNEYSLEEPER = 230,
	WEAPON_DARWINDANGERSHIELD,
	WEAPON_BUSHWACKA,
	WEAPON_ROCKETJUMPER = 237,
	WEAPON_GRU = 239,
	WEAPON_FRYINGPAN = 264,
	WEAPON_STICKYJUMPER,
	WEAPON_HEADTAKER,
	WEAPON_NEWLUGERMORPH = 294,
	WEAPON_IRONCURTAIN = 298,
	WEAPON_AMPUTATOR = 304,
	WEAPON_CRUSADERCROSSBOW,
	WEAPON_ULTRAPOOLCABER = 307,
	WEAPON_LOCHNLOAD,
	WEAPON_WARRIORSPIRIT = 310,
	WEAPON_BRASSBEAST,
	WEAPON_CANDYCANE = 317,
	WEAPON_BOSTONBASHER = 325,
	WEAPON_BACKSCRATCHER,
	WEAPON_CLAIDHEAMHMOR,
	WEAPON_JAG = 329,
	WEAPON_FISTSOFSTEEEL = 331,
	WEAPON_SHARPENEDVOLCANOFRAGMENT = 348,
	WEAPON_STUNONASTICK,
	WEAPON_DETONATOR = 351,
	WEAPON_CONCHEROR = 354,
	WEAPON_FANOWAR,
	WEAPON_CONNIVERKUNAI,
	WEAPON_HALFZATOCHI,
	WEAPON_SHAHANSHAH = 401,
	WEAPON_BAZAARBARGAIN,
	WEAPON_PERSIANPERSUADER = 404,
	WEAPON_WEEBOOTIES,
	WEAPON_SPLENDIDSCREEN,
	WEAPON_QUICKFIX = 411,
	WEAPON_OVERDOESE,
	WEAPON_SOLEMNVOW,
	WEAPON_LIBERTYLAUNCHER,
	WEAPON_RESERVESHOOTER,
	WEAPON_MARKETGARDENER,
	WEAPON_SAXXY = 423,
	WEAPON_TOMISLAV,
	WEAPON_FAMILYBUSINESS,
	WEAPON_EVICTIONNOTICE,
	WEAPON_FISHCAKE = 433,
	WEAPON_COWMANGLER = 441,
	WEAPON_RIGHTEOUSBISON,
	WEAPON_MANTREADS = 444,
	WEAPON_DISCIPLINARYACTION = 447,
	WEAPON_SODAPOPPER,
	WEAPON_WINGER,
	WEAPON_ATOMIZER,
	WEAPON_THREERUNEBLADE = 452,
	WEAPON_POSTALPUMMELER = 457,
	WEAPON_ENFORCER = 460,
	WEAPON_BIGEARNER,
	WEAPON_MAUL = 466,
	WEAPON_CONSCIENTIOUSOBJECTOR = 474,
	WEAPON_NINEIRON = 482,
	WEAPON_ORIGINAL = 513,
	WEAPON_DIAMONDBACK = 525,
	WEAPON_MACHINA,
	WEAPON_WIDOWMAKER,
	WEAPON_SHORTCIRCUIT,
	WEAPON_UNARMEDCOMBAT = 572,
	WEAPON_WANGAPRICK = 574,
	WEAPON_APOCOFISTS = 587,
	WEAPON_PONSON6000,
	WEAPON_EUREKAEFFECT,
	WEAPON_THIRDDEGREE = 593,
	WEAPON_PHLOGISTINATOR,
	WEAPON_MALMELTER,
	WEAPON_BOOTLEGGER = 608,
	WEAPON_SCOTTISHHANDSHAKE,
	WEAPON_SHARPDRESSER = 638,
	WEAPON_COZYCAMPER = 642,
	WEAPON_WEAPASSASSIN = 648,
	WEAPON_SPYCICLE,
	WEAPON_FESTIVEMINIGUN = 654,
	WEAPON_HOLIDAYPUNCH = 656,
	WEAPON_FESTIVEROCKETLAUNCHER = 658,
	WEAPON_FESTIVEFLAMETHROWER,
	WEAPON_FESTIVEBAT,
	WEAPON_FESTIVESTICKYBOMBLAUNCHER,
	WEAPON_FESTIVEWRENCH,
	WEAPON_FESTIVEMEDIGUN,
	WEAPON_FESTIVESNIPERRIFLE,
	WEAPON_FESTIVEKNIFE,
	WEAPON_FESTIVESCATTERGUN = 669,
	WEAPON_BLACKROSE = 727,
};
