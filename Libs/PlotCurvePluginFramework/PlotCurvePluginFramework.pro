TEMPLATE = subdirs
CONFIG   += ordered
SUBDIRS += \
    ICurve \
    CurveRaw \
    CurveUsrPos\
    CurveUsrPerr\
    CurveUsrVffd\
    CurveUsrVcmd\
    CurveUsrVfb\
    CurveUsrVel\
    CurveUsrIcmd\
    CurveUsrIfb\
    CurveUsrIu\
    CurveUsrIv\
    CurveUsrIw\
    CurveUsrTq\
	CurveUsrTrate\
    PluginsManager

TRANSLATIONS    += ch_plugins.ts en_plugins.ts
