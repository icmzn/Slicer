/*==============================================================================

  Copyright (c) Laboratory for Percutaneous Surgery (PerkLab)
  Queen's University, Kingston, ON, Canada. All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Csaba Pinter, PerkLab, Queen's University
  and was supported through the Applied Cancer Research Unit program of Cancer Care
  Ontario with funds provided by the Ontario Ministry of Health and Long-Term Care
  and CANARIE.

==============================================================================*/

// MRML includes
#include "vtkMRMLMultiVolumeRenderingDisplayNode.h"

// VTK includes
#include <vtkObjectFactory.h>

// STL includes
#include <sstream>

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLMultiVolumeRenderingDisplayNode);

//----------------------------------------------------------------------------
vtkMRMLMultiVolumeRenderingDisplayNode::vtkMRMLMultiVolumeRenderingDisplayNode()
{
  this->RaycastTechnique = vtkMRMLMultiVolumeRenderingDisplayNode::Composite;
  this->SurfaceSmoothing = false;
}

//----------------------------------------------------------------------------
vtkMRMLMultiVolumeRenderingDisplayNode::~vtkMRMLMultiVolumeRenderingDisplayNode()
{
}

//----------------------------------------------------------------------------
void vtkMRMLMultiVolumeRenderingDisplayNode::ReadXMLAttributes(const char** atts)
{
  this->Superclass::ReadXMLAttributes(atts);

  vtkMRMLReadXMLBeginMacro(atts);
  vtkMRMLReadXMLIntMacro(raycastTechnique, RaycastTechnique);
  vtkMRMLReadXMLIntMacro(surfaceSmoothing, SurfaceSmoothing);
  vtkMRMLReadXMLEndMacro();
}

//----------------------------------------------------------------------------
void vtkMRMLMultiVolumeRenderingDisplayNode::WriteXML(ostream& of, int nIndent)
{
  this->Superclass::WriteXML(of, nIndent);

  vtkMRMLWriteXMLBeginMacro(of);
  vtkMRMLWriteXMLIntMacro(raycastTechnique, RaycastTechnique);
  vtkMRMLWriteXMLIntMacro(surfaceSmoothing, SurfaceSmoothing);
  vtkMRMLWriteXMLEndMacro();
}

//----------------------------------------------------------------------------
void vtkMRMLMultiVolumeRenderingDisplayNode::Copy(vtkMRMLNode *anode)
{
  int wasModifying = this->StartModify();
  this->Superclass::Copy(anode);

  vtkMRMLCopyBeginMacro(anode);
  vtkMRMLCopyIntMacro(RaycastTechnique);
  vtkMRMLCopyIntMacro(SurfaceSmoothing);
  vtkMRMLCopyEndMacro();

  this->EndModify(wasModifying);
}

//----------------------------------------------------------------------------
void vtkMRMLMultiVolumeRenderingDisplayNode::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  vtkMRMLPrintBeginMacro(os, indent);
  vtkMRMLPrintIntMacro(RaycastTechnique);
  vtkMRMLPrintIntMacro(SurfaceSmoothing);
  vtkMRMLPrintEndMacro();
}
