/**
 * Copyright (C) 2011 Jorge Jimenez (jorge@iryoku.com). All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are 
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of the copyright holders.
 */


#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <d3d10.h>
#include <d3dx10.h>
#include <dxerr.h>
#include <dxgi.h>

class Camera {
    public:
        Camera() :
            distance(0.0f),
            angle(0.0f, 0.0f),
            angularVelocity(0.0f, 0.0f),
            panPosition(0.0f, 0.0f),
            viewportSize(1.0f, 1.0f),
            mousePos(0.0f, 0.0f),
            attenuation(0.0f),
            draggingLeft(false),
            draggingMiddle(false),
            draggingRight(false) { build(); }

        LRESULT handleMessages(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        void frameMove(FLOAT elapsedTime);

        void setDistance(float distance) { this->distance = distance; }
        float getDistance() const { return distance; }

        void setPanPosition(const XMFLOAT2 &panPosition) { this->panPosition = panPosition; }
        const XMFLOAT2 &getPanPosition() const { return panPosition; }

        void setAngle(const XMFLOAT2 &angle) { this->angle = angle; }
        const XMFLOAT2 &getAngle() const { return angle; }

        void setAngularVelocity(const XMFLOAT2 &angularVelocity) { this->angularVelocity = angularVelocity; }
        const XMFLOAT2 &getAngularVelocity() const { return angularVelocity; }

        void setProjection(float fov, float aspect, float zn, float zf);
        void setJitteredProjection(float fov, float aspect, float zn, float zf, const XMFLOAT2 &jitter);
        void setViewportSize(const XMFLOAT2 &viewportSize) { this->viewportSize = viewportSize; }

        const XMMATRIX &getViewMatrix() { return view; }
        const XMMATRIX &getProjectionMatrix() const { return projection; }

        const XMFLOAT3 &getLookAtPosition() { return lookAtPosition; }  
        const XMFLOAT3 &getEyePosition() { return eyePosition; }  

        friend std::ostream& operator <<(std::ostream &os, const Camera &camera);
        friend std::istream& operator >>(std::istream &is, Camera &camera);

    private:
        void build();
        void updatePosition(XMFLOAT2 delta);

        XMMATRIX jitteredFrustum(float left, float right, float bottom, float top, float zn, float zf, 
                                   float pixdx, float pixdy, float eyedx, float eyedy, float focus) const;
        XMMATRIX jitteredPerspective(float fovy, float aspect, float zn, float zf, 
                                       float pixdx, float pixdy, float eyedx, float eyedy, float focus) const;

        float distance;
        XMFLOAT2 panPosition;
        XMFLOAT2 angle, angularVelocity;
        XMFLOAT2 viewportSize;

        XMMATRIX view, projection;
        XMFLOAT3 lookAtPosition;
        XMFLOAT3 eyePosition;

        XMFLOAT2 mousePos;
        float attenuation;
        bool draggingLeft, draggingMiddle, draggingRight;
};

#endif
