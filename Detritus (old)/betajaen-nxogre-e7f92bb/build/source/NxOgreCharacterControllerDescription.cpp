/** 
    
    This file is part of NxOgre.
    
    Copyright (c) 2009 Robin Southern, http://www.nxogre.org
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
    
*/

                                                                                       

#include "NxOgreStable.h"
#include "NxOgreCharacterControllerDescription.h"

#if NxOgreHasCharacterController == 1

                                                                                       

namespace NxOgre
{

                                                                                       

CharacterControllerDescription::CharacterControllerDescription()
{
 reset();
}

void CharacterControllerDescription::reset()
{
 mUpDirection = Enums::Y;
 mSlopeLimit = 0.707;
 mSkinWidth = 0.1;
 mCallback = 0;
 mStepOffset = 0.5f;
 mCapsuleEasyClimbing = false;
 mName.clear();
}

bool CharacterControllerDescription::isValid() const
{
 if (mSlopeLimit < 0)
  return false;
 if (mSkinWidth < 0)
  return false;
 if (mStepOffset < 0)
  return false;
 return true;
}

                                                                                       

} // namespace NxOgre

                                                                                       

#endif