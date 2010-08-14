#include <stdio.h>
#include <exception>
#include <assert.h>

#include "md2_loader.h"
#include "base_3d_app.h"

class MD2Viewer : public Base3DApplication
{
public:
    MD2Viewer(int WindowWidth, int WindowHeight);
    ~MD2Viewer();

    void UpdateFrame();

    void OnKeyboard(unsigned char Key, int x, int y);

    void OnSpecialKeys(int Key, int x, int y);

    void OnPassiveMouseMov(int x, int y);

    void OnMouseMov(int x, int y);

private:

    ICamera*  m_pCamera1;
    ICamera*  m_pCamera2;
    ICamera*  m_pCurrentCamera;
    ILight*   m_pDirectionalLight;
    ILight*   m_pPointLight;
    ILight*   m_pSpotLight;
    ITexture* m_pColorMap;
    ITexture* m_pBumpMap;
    IMesh*    m_pMesh;
};

MD2Viewer::MD2Viewer(int WindowWidth, int WindowHeight) :
	Base3DApplication(WindowWidth, WindowHeight)
{
   /* m_pDirectionalLight = m_pColossus->CreateLight(LIGHT_TYPE_DIRECTIONAL_LIGHT);
    m_pDirectionalLight->SetAmbient(0.0f, 0.0f, 0.0f);
    m_pDirectionalLight->SetDiffuse(0.0f, 0.0f, 0.0f);
    m_pDirectionalLight->SetSpecular(0.0f, 0.0f, 0.0f);
    m_pDirectionalLight->SetAttenuation(1.0f, 0.001f, 0.0001f);
    m_pDirectionalLight->SetPos(0.0f, 100.0f, -2.5f);
    m_pDirectionalLight->SetExponent(4.0f);
    m_pDirectionalLight->TurnOn();*/

    m_pPointLight = m_pColossus->CreateLight(LIGHT_TYPE_POINT_LIGHT);    
    m_pPointLight->SetAmbient(0.4f, 0.4f, 0.4f);
    m_pPointLight->SetDiffuse(0.8f, 0.8f, 0.8f);
    m_pPointLight->SetSpecular(0.2f, 0.2f, 0.2f);
    m_pPointLight->SetAttenuation(1.0f, 0.000f, 0.0000f);
    m_pPointLight->SetPos(1.0f, 10.0f, -3.0f);
    m_pPointLight->SetExponent(4.0f);
    m_pPointLight->TurnOn();

    m_pSpotLight  = m_pColossus->CreateLight(LIGHT_TYPE_SPOT_LIGHT);
    m_pSpotLight->SetAmbient(0.0f, 0.0f, 0.0f);
    m_pSpotLight->SetDiffuse(0.0f, 0.0f, 0.0f);
    m_pSpotLight->SetSpecular(0.8f, 0.8f, 0.8f);
    m_pSpotLight->SetAttenuation(1.0f, 0.0001f, 0.00001f);
    m_pSpotLight->SetPos(1.0f, 10.0f, -3.0f);
    m_pSpotLight->SetDirection(0.0f, 0.0f, 0.0f);
    m_pSpotLight->SetCutoff(0.7f);
    m_pSpotLight->SetExponent(2.0f);
    m_pSpotLight->TurnOn();
    
    m_pMesh = m_pColossus->CreateMeshBox("box");
    m_pMesh->AddToFrame();

    m_pColorMap = m_pColossus->CreateTexture(COLOSSUS_TEXTURE_TYPE_2D);
    m_pColorMap->Load2D("/home/cl/hacking/graphics/media/stone.dds");
    
    m_pBumpMap = m_pColossus->CreateTexture(COLOSSUS_TEXTURE_TYPE_2D);
    m_pBumpMap->Load2D("/home/cl/hacking/graphics/media/stone_normal.dds");

    m_pMesh->SetColorMap(m_pColorMap);
    m_pMesh->SetBumpMap(m_pBumpMap);

    Vector3f Pos(0.0f, 0.0f, 2.0f);
    const Vector3f Target(0.0f, 0.0f, 0.0f);
    const Vector3f Up(0.0f, 1.0f, 0.0f);

    m_pCamera1 = m_pColossus->CreateCamera(WindowWidth, WindowHeight, Pos, Target, Up);
    m_pColossus->SetCurrentCamera(m_pCamera1);
    m_pCurrentCamera = m_pCamera1;
    m_pCamera1->SetVelocity(15.0f);

    Pos.x = -2.0f;
    m_pCamera2 = m_pColossus->CreateCamera(WindowWidth, WindowHeight, Pos, Target, Up);
}


MD2Viewer::~MD2Viewer()
{
    if (m_pColorMap)
        m_pColossus->DestroyTexture(m_pColorMap);

    if (m_pBumpMap)
        m_pColossus->DestroyTexture(m_pBumpMap);

    if (m_pDirectionalLight)
        m_pColossus->DestroyLight(m_pDirectionalLight);

    if (m_pPointLight)
        m_pColossus->DestroyLight(m_pPointLight);

    if (m_pSpotLight)
        m_pColossus->DestroyLight(m_pSpotLight);

    if (m_pMesh)
        m_pColossus->DestroyMesh(m_pMesh);
    
    if (m_pCamera1)
        m_pColossus->DestroyCamera(m_pCamera1);

    if (m_pCamera2)
        m_pColossus->DestroyCamera(m_pCamera2);
}


void MD2Viewer::UpdateFrame()
{
}


void MD2Viewer::OnKeyboard(unsigned char Key, int x, int y)
{
    switch (Key) {
        case ' ':
            if (m_pMesh->GetBumpMap()) {
                m_pMesh->SetBumpMap(NULL);
            }
            else {
                m_pMesh->SetBumpMap(m_pBumpMap);
            }
            break;

        case 'c':
            if (m_pCurrentCamera == m_pCamera1) {
                m_pCurrentCamera = m_pCamera2;
            }
            else {
                m_pCurrentCamera = m_pCamera1;
            }

            m_pColossus->SetCurrentCamera(m_pCurrentCamera);
            break;

        default:
        Base3DApplication::OnKeyboard(Key, x, y);
    }
}

void MD2Viewer::OnSpecialKeys(int Key, int x, int y)
{
    m_pCurrentCamera->OnKeyboard(Key, x, y);
}


void MD2Viewer::OnPassiveMouseMov(int x, int y)
{
    m_pCurrentCamera->OnPassiveMouseMov(x, y);
}

void MD2Viewer::OnMouseMov(int x, int y)
{
    m_pCurrentCamera->OnPassiveMouseMov(x, y);
}


int main (int argc, char *argv[])
{
    try {
        MD2Loader md2("/home/cl/hacking/graphics/models/md2/modelpack1/Model1/pilaar.md2");
//        MD2Viewer App(1280, 1024);
  //      App.Run();
    } catch (std::string& e) {
        printf("Caught exception: %s\n", e.c_str());
        return 1;
    }

    return(0);
}
