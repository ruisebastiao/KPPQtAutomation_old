TEMPLATE = subdirs

SUBDIRS += \
    KPPCommon \    
    icxmlserializable \
    KPPHardware \
    KPPVision


CONFIG += ordered
SUBDIRS += QtVision

#CONFIG += ordered


#TRANSLATIONS = QtVision\resources\translate\entr_pt.ts
#TRANSLATIONS = KPPCommon\entr_pt.ts
