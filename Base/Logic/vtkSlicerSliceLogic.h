/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkSlicerSliceLogic.h,v $
  Date:      $Date: 2006/01/08 04:48:05 $
  Version:   $Revision: 1.45 $

=========================================================================auto=*/

// .NAME vtkSlicerSliceLogic - slicer logic class for slice manipulation
// .SECTION Description
// This class manages the logic associated with display of slice windows
// (but not the GUI).  Features of the class include:
//  -- a back-to-front list of MrmlVolumes to be displayed
//  -- a compositing mode for each volume layer (opacity, outline, glyph, checkerboard, etc)
//  -- each layer is required to provide an RGBA image in the space defined by the vtkMRMLSliceNode
//
// This class manages internal vtk pipelines that create an output vtkImageData
// which can be used by the vtkSlicerSliceGUI class to display the resulting
// composite image or it can be used as a texture map in a vtkSlicerView.
// This class can also be used for resampling volumes for further computation.


#ifndef __vtkSlicerSliceLogic_h
#define __vtkSlicerSliceLogic_h

#include <stdlib.h>

#include "vtkSlicerBaseLogic.h"
#include "vtkSlicerLogic.h"

#include "vtkMRML.h"
#include "vtkMRMLSliceNode.h"
#include "vtkMRMLSliceCompositeNode.h"
#include "vtkSlicerSliceLayerLogic.h"
#include "vtkSlicerSliceGlyphLogic.h"
#include "vtkMRMLModelNode.h"

#include "vtkImageBlend.h"
#include "vtkCollection.h"
#include "vtkPolyDataCollection.h"

class vtkImageData;
class vtkMRMLModelDisplayNode;

class VTK_SLICER_BASE_LOGIC_EXPORT vtkSlicerSliceLogic : public vtkSlicerLogic 
{
  public:
  
  // The Usual vtk class functions
  static vtkSlicerSliceLogic *New();
  vtkTypeRevisionMacro(vtkSlicerSliceLogic,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // The mrml slice node for this slice logic
  vtkGetObjectMacro (SliceNode, vtkMRMLSliceNode);
  void SetSliceNode (vtkMRMLSliceNode *SliceNode);

  // Description:
  // The mrml slice node for this slice logic
  vtkGetObjectMacro (SliceCompositeNode, vtkMRMLSliceCompositeNode);
  void SetSliceCompositeNode (vtkMRMLSliceCompositeNode *SliceCompositeNode);

  // Description:
  // The background slice layer
  // TODO: this will eventually be generalized to a list of layers
  vtkGetObjectMacro (BackgroundLayer, vtkSlicerSliceLayerLogic);
  void SetBackgroundLayer (vtkSlicerSliceLayerLogic *BackgroundLayer);

  // Description:
  // The forground slice layer
  // TODO: this will eventually be generalized to a list of layers
  vtkGetObjectMacro (ForegroundLayer, vtkSlicerSliceLayerLogic);
  void SetForegroundLayer (vtkSlicerSliceLayerLogic *ForegroundLayer);

  // Description:
  // The background slice glyph layer
  // TODO: this will eventually be generalized to a list of layers
  vtkGetObjectMacro (BackgroundGlyphLayer, vtkSlicerSliceGlyphLogic);
  void SetBackgroundGlyphLayer (vtkSlicerSliceGlyphLogic *BackgroundLayer);

  // Description:
  // The forground slice layer
  // TODO: this will eventually be generalized to a list of layers
  vtkGetObjectMacro (ForegroundGlyphLayer, vtkSlicerSliceGlyphLogic);
  void SetForegroundGlyphLayer (vtkSlicerSliceGlyphLogic *ForegroundGlyphLayer);

  // Description:
  // The Label slice layer
  // TODO: this will eventually be generalized to a list of layers
  vtkGetObjectMacro (LabelLayer, vtkSlicerSliceLayerLogic);
  void SetLabelLayer (vtkSlicerSliceLayerLogic *LabelLayer);

  // Description:
  // The opacity of the forground slice layer
  // TODO: this will eventually be generalized to a per-layer compositing function
  // -- could be checkerboard or other filter
  vtkGetMacro (ForegroundOpacity, double);
  void SetForegroundOpacity (double ForegroundOpacity);

  // Description:
  // The opacity of the Label slice layer
  // TODO: this will eventually be generalized to a per-layer compositing function
  // -- could be checkerboard or other filter
  vtkGetMacro (LabelOpacity, double);
  void SetLabelOpacity (double LabelOpacity);

  // Description:
  // Model slice plane 
  vtkGetObjectMacro (SliceModelNode, vtkMRMLModelNode);

  // Description:
  // The compositing filter
  // TODO: this will eventually be generalized to a per-layer compositing function
  vtkGetObjectMacro (Blend, vtkImageBlend);

  // Description:
  // All the PolyData objects to render
  vtkGetObjectMacro (PolyDataCollection, vtkPolyDataCollection);

  // Description:
  // All the LookupTable objects to color the PolyData object
  vtkGetObjectMacro (LookupTableCollection, vtkCollection);

  // Description:
  // the tail of the pipeline
  // -- returns NULL if none of the inputs exist
  vtkImageData *GetImageData () { 
     if ( (this->GetBackgroundLayer() != NULL && this->GetBackgroundLayer()->GetImageData() != NULL) ||
         (this->GetForegroundLayer() != NULL && this->GetForegroundLayer()->GetImageData() != NULL) ||
         (this->GetLabelLayer() != NULL && this->GetLabelLayer()->GetImageData() != NULL) ) 
      {     
      return this->ImageData;
      }
     else
      {
      return NULL;
      }
  };

  void UpdateImageData () { 
    if ( (this->GetBackgroundLayer() != NULL && this->GetBackgroundLayer()->GetImageData() != NULL) ||
         (this->GetForegroundLayer() != NULL && this->GetForegroundLayer()->GetImageData() != NULL) ||
         (this->GetLabelLayer() != NULL && this->GetLabelLayer()->GetImageData() != NULL) ) 
      {     
      this->Blend->Update(); 
      if (this->Blend->GetOutput()->GetMTime() > this->ImageData->GetMTime())
        {
        this->ImageData->DeepCopy( this->Blend->GetOutput()); 
        }
      }
  };

  // Description:
  // update the pipeline to reflect the current state of the nodes
  void UpdatePipeline ();

  // Description:
  // provide the virtual method that updates this Logic based
  // on mrml changes and one that updates based on changes in 
  // the input logic (the slice layers in this case)
  virtual void ProcessMRMLEvents ( vtkObject * /*caller*/, 
                                  unsigned long /*event*/, 
                                  void * /*callData*/ );
  virtual void ProcessMRMLEvents () { this->ProcessMRMLEvents( NULL, vtkCommand::NoEvent, NULL ); };

  // Description:
  // process logic events
  virtual void ProcessLogicEvents ( vtkObject * /*caller*/, 
                                  unsigned long /*event*/, 
                                  void * /*callData*/ ) {this->ProcessLogicEvents();};
  void ProcessLogicEvents(); 

  // Description:
  // manage and syncronise the SliceNode
  void UpdateSliceNode();

  // Description:
  // Upadte slicer node given a layout name
  void UpdateSliceNodeFromLayout();

  // Description:
  // manage and syncronise the SliceCompositeNode
  void UpdateSliceCompositeNode();

  // Description:
  // Get the size of the volume, transformed to RAS space
  void GetBackgroundRASBox(double rasDimensions[3], double rasCenter[3]);

  // Description:
  // Get the size of the volume, transformed to slice space
  void GetBackgroundSliceDimensions(double sliceDimensions[3], double sliceCenter[3]);

  // Description:
  // Get the spacing of the volume, transformed to slice space 
  // - to be used, for example, to set the slice increment for stepping a single 
  //   voxel relative to the current slice view
  double *GetBackgroundSliceSpacing();

  // Description:
  // Get the min/max bounds of the volume
  // - note these are not translated by the current slice offset so they can
  //   be used to calculate the range (e.g. of a slider) that operates in slice space
  void GetBackgroundSliceBounds(double sliceBounds[6]);

  // Description:
  // adjust the node's field of view to match the extent of current background volume
  void FitSliceToBackground(int width, int height);

  // Description:
  // adjust the node's field of view to match the extent of all volume layers
  // TODO: not yet implemented
  void FitSliceToAll(int width, int height);

  // Description:
  // Get/Set the current distance from the origin to the slice plane
  double GetSliceOffset();
  void SetSliceOffset(double offset);

  // Description:
  // Make a slice model with the current configuration
  void CreateSliceModel();
  void DeleteSliceModel();

protected:
  vtkSlicerSliceLogic();
  ~vtkSlicerSliceLogic();
  vtkSlicerSliceLogic(const vtkSlicerSliceLogic&);
  void operator=(const vtkSlicerSliceLogic&);

  // Description:
  //
  vtkMRMLSliceNode *SliceNode;
  vtkMRMLSliceCompositeNode *SliceCompositeNode;
  vtkSlicerSliceLayerLogic *BackgroundLayer;
  vtkSlicerSliceLayerLogic *ForegroundLayer;
  vtkSlicerSliceLayerLogic *LabelLayer;

  vtkSlicerSliceGlyphLogic *ForegroundGlyphLayer;
  vtkSlicerSliceGlyphLogic *BackgroundGlyphLayer;

  double ForegroundOpacity;
  double LabelOpacity;
  vtkImageBlend *Blend;
  vtkImageData *ImageData;

  vtkPolyDataCollection *PolyDataCollection;
  vtkCollection *LookupTableCollection;

  vtkMRMLModelNode *SliceModelNode;
  vtkMRMLModelDisplayNode *SliceModelDisplayNode;
  double SliceSpacing[3];

};

#endif

