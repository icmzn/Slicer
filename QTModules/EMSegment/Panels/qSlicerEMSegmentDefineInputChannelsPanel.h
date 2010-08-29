#ifndef __qSlicerEMSegmentDefineInputChannelsPanel_h
#define __qSlicerEMSegmentDefineInputChannelsPanel_h 

// CTK includes
#include <ctkPimpl.h>

// EMSegment includes
#include "qSlicerEMSegmentWidget.h"

#include "qSlicerEMSegmentModuleExport.h"

class qSlicerEMSegmentDefineInputChannelsPanelPrivate;
class qSlicerEMSegmentInputChannelListWidget;

class Q_SLICER_QTMODULES_EMSEGMENT_EXPORT qSlicerEMSegmentDefineInputChannelsPanel :
    public qSlicerEMSegmentWidget
{ 
  Q_OBJECT

public:

  typedef qSlicerEMSegmentWidget Superclass;
  qSlicerEMSegmentDefineInputChannelsPanel(QWidget *newParent=0);

  void updateMRMLFromWidget();

  qSlicerEMSegmentInputChannelListWidget * inputChannelListWidget()const;

private:
  CTK_DECLARE_PRIVATE(qSlicerEMSegmentDefineInputChannelsPanel);
};

#endif
