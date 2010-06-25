/*
 *  Copyright (c) 2010 Lukáš Tvrdý <lukast.dev@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KIS_ABR_TRANSLATOR_H
#define KIS_ABR_TRANSLATOR_H


#include <QString>
#include <QDomDocument>
const QString ABR_PRESET_START = "START";

const QString ABR_OBJECT = "Objc";
const QString ABR_PRESET_NAME = "Nm  ";
const QString ABR_BRUSH_DIAMETER = "Dmtr";
const QString ABR_BRUSH_HARDNESS = "Hrdn";
const QString ABR_BRUSH_ANGLE = "Angl";
const QString ABR_BRUSH_ROUNDNESS = "Rndn";
const QString ABR_BRUSH_SPACING = "Spcn";
const QString ABR_BRUSH_INTR = "Intr";
const QString ABR_BRUSH_FLIP_X = "flipX";
const QString ABR_BRUSH_FLIP_Y = "flipY";
const QString ABR_USE_TIP_DYNAMICS = "useTipDynamics";
const QString ABR_TIP_DYNAMICS_MINUMUM_DIAMETER = "minimumDiameter";
const QString ABR_TIP_DYNAMICS_MINUMUM_ROUNDNESS = "minimumRoundness";
const QString ABR_TIP_DYNAMICS_TILT_SCALE = "tiltScale"; 
const QString ABR_SZVR = "szVr"; // size variance?
const QString ABR_DYNAMICS_FADE_STEP = "fStp";
const QString ABR_DYNAMICS_JITTER = "jitter";
const QString ABR_ANGLE_DYNAMICS = "angleDynamics";
const QString ABR_CONTROL = "bVTy"; // control of the attribute 
const QString ABR_ROUNDNESS_DYNAMICS = "roundnessDynamics";
const QString ABR_USE_SCATTER = "useScatter";
const QString ABR_DUAL_BRUSH = "dualBrush";
const QString ABR_USE_DUAL_BRUSH = "useDualBrush";
const QString ABR_BRUSH_GROUP = "brushGroup";
const QString ABR_USE_BRUSH_GROUP = "useBrushGroup";
const QString ABR_USE_TEXTURE = "useTexture";
const QString ABR_USE_PAINT_DYNAMICS = "usePaintDynamics";
const QString ABR_USE_COLOR_DYNAMICS = "useColorDynamics";
const QString ABR_WET_EDGES = "Wtdg";
const QString ABR_NOISE = "Nose";
const QString ABR_AIRBRUSH = "Rpt "; // repeat

// TODO: if string comaprisons would be slow, convert it to enum 
enum enumObjectTypes {BRUSH_PRESET, BRUSH, SIZE_VARIANCE, ANGLE_DYNAMICS, ROUNDNESS_DYNAMICS, DUAL_BRUSH, COUNT_DYNAMICS, SCATTER_DYNAMICS, BRUSH_GROUP};
const QString OBJECT_NAME_BRUSH_PRESET = "";
const QString OBJECT_NAME_BRUSH = "Brsh";
const QString OBJECT_NAME_SIZE_VARIANCE = "szVr";
const QString OBJECT_NAME_ANGLE_DYNAMICS = "angleDynamics";
const QString OBJECT_NAME_ROUNDNESS_DYNAMICS = "roundnessDynamics";
const QString OBJECT_NAME_DUAL_BRUSH = "dualBrush";
const QString OBJECT_NAME_COUNT_DYNAMICS = "countDynamics";
const QString OBJECT_NAME_SCATTER_DYNAMICS = "scatterDynamics";
const QString OBJECT_NAME_BRUSH_GROUP = "brushGroup";
const QString OBJECT_NAME_FLOW_JITTER = "prVr";
const QString OBJECT_NAME_OPACITY_VARIANCE = "opVr";

const QString BRUSH_TYPE_COMPUTED = "computedBrush";
const QString BRUSH_TYPE_SAMPLED = "sampledBrush";

enum enumAbrControllers{ OFF, FADE, PEN_PRESSURE, PEN_TILT, STYLUS_WHEEL, ROTATION, INITIAL_DIRECTION, DIRECTION};


class AbrBrushProperties{
public:
    void toXML(QDomDocument& , QDomElement&) const;
    void setupProperty(const QString &attributeName,const QString &type,const  QString &value);
private:
    double m_diameter;
    double m_hardness;
    double m_angle;
    double m_roundness;
    double m_spacing;
    bool m_intr;
    bool m_flipX;
    bool m_flipY;
    
    QString m_brushType;
};

class AbrShapeDynamicsProperties{
public:
    bool useTipDynamics;
    bool flipX;
    bool flipY;
    double minumumDiameter;
    double minumumRoundness;
    double tiltScale;
public:
    void toXML(QDomDocument& , QDomElement&) const;
};


class AbrGroupProperties{
public:
    enumAbrControllers bVTy;
    int fadeStep;
    double sizeJitter;
public:    
    void toXML(QDomDocument& , QDomElement&) const;
};


class AbrAngleDynamicsProperties{
public:
    AbrGroupProperties group;
    void toXML(QDomDocument& , QDomElement&) const;
};

class AbrRoundnessDynamicsProperties{
public:
    AbrGroupProperties group;
    bool useScatter;
    void toXML(QDomDocument& , QDomElement&) const;
};

class AbrDualBrushProperties{
public:
       bool useDualBrush; 
       void toXML(QDomDocument& , QDomElement&) const;
};

class AbrBrushGroupProperties{
public:
    bool useBrushGroup;
    bool useTexture;
    bool usePaintDynamics;
    bool useColorDynamics;
    bool wetEdges;
    bool noise;
    bool repeat;
    void toXML(QDomDocument& , QDomElement&) const;
};

class KisAbrTranslator{
    public:
        KisAbrTranslator();
        ~KisAbrTranslator();
        
        
        void addEntry(const QString &attributeName,const QString &type,const  QString &value);
        
        QString toString();
        void finishPreset();
        void clean();

    private:
        void init();
        void setupObjectType(const QString &type);
        void setupBrush(const QString &attributeName,const QString &type,const  QString &value);
    private:
        QDomDocument m_doc;
        QDomElement m_root;
        QString m_currentObjectName;
        AbrBrushProperties m_abrBrushProperties;
        
};

#endif