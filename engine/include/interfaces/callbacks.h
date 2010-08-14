/*

	Copyright 2010 Etay Meiri

	This file is part of Colossus

    Colossus is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Colosssus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Colosssus.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef _I3DCALLBACKS_H_
#define _I3DCALLBACKS_H_

class IColossusCallbacks
{
public:
    virtual void OnRender() = 0;

    virtual void OnChangeSize(int w, int h) = 0;

    virtual void OnTimer(int Value) = 0;

    virtual void OnSpecialKeys(int Key, int x, int y) = 0;

    virtual void OnKeyboard(unsigned char Key, int x, int y) = 0;

    virtual void OnPassiveMouseMov(int x, int y) = 0;

    virtual void OnMouseMov(int x, int y) = 0;
};


#endif
