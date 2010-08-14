#include <stdio.h>
#include <exception>
#include <assert.h>
#include <math.h>

#include "base_3d_app.h"

class SolarExplorer : public Base3DApplication
{
public:
    SolarExplorer(int WindowWidth, int WindowHeight);
    ~SolarExplorer();

    void UpdateFrame();

    void OnKeyboard(unsigned char Key, int x, int y);

    void OnSpecialKeys(int Key, int x, int y);

    void OnPassiveMouseMov(int x, int y);

    void OnMouseMov(int x, int y);

private:

    void CreateCamera();
    void CreateLights();
    void CreateObjects();

    int m_windowWidth;
    int m_windowHeight;

    ICamera*  m_pCamera1;
    ICamera*  m_pCurrentCamera;
    ILight*   m_pDirectionalLight;
    ILight*   m_pPointLight;
    ILight*   m_pSpotLight;

    IMesh*    m_pStar;
    ITexture* m_pStarColorMap;
    ITexture* m_pStarBumpMap;
    ITexture* m_pSkyBoxMap;
    
    IMesh*    m_pSpaceship;
    ITexture* m_pSpaceshipColorMap;
    float     m_spaceshipAngle;
};

SolarExplorer::SolarExplorer(int WindowWidth, int WindowHeight) :
	Base3DApplication(WindowWidth, WindowHeight)
{
    m_windowWidth = WindowWidth;
    m_windowHeight = WindowHeight;
    m_spaceshipAngle = 0.0f;

    CreateObjects();
    CreateLights();
    CreateCamera();
}


SolarExplorer::~SolarExplorer()
{
    if (m_pStarBumpMap)
        m_pColossus->DestroyTexture(m_pStarBumpMap);

    if (m_pStarColorMap)
        m_pColossus->DestroyTexture(m_pStarColorMap);

    if (m_pSpaceshipColorMap)
        m_pColossus->DestroyTexture(m_pSpaceshipColorMap);

    if (m_pSkyBoxMap)
        m_pColossus->DestroyTexture(m_pSkyBoxMap);

    if (m_pDirectionalLight)
        m_pColossus->DestroyLight(m_pDirectionalLight);

    if (m_pPointLight)
        m_pColossus->DestroyLight(m_pPointLight);

    if (m_pSpotLight)
        m_pColossus->DestroyLight(m_pSpotLight);

    if (m_pStar)
        m_pColossus->DestroyMesh(m_pStar);

    if (m_pSpaceship)
        m_pColossus->DestroyMesh(m_pSpaceship);
    
    if (m_pCamera1)
        m_pColossus->DestroyCamera(m_pCamera1);
}

void SolarExplorer::CreateCamera()
{
    Vector3f Pos(0.0f, 0.0f, 120.0f);
    const Vector3f Target(0.0f, 0.0f, 0.0f);
    const Vector3f Up(0.0f, 1.0f, 0.0f);

    m_pCamera1 = m_pColossus->CreateCamera(m_windowWidth, m_windowHeight, Pos, Target, Up);
    m_pColossus->SetCurrentCamera(m_pCamera1);
    m_pCurrentCamera = m_pCamera1;
    m_pCamera1->SetVelocity(100.0f);
}

void SolarExplorer::CreateLights()
{
    /*m_pDirectionalLight = m_pColossus->CreateLight(LIGHT_TYPE_DIRECTIONAL_LIGHT);
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
    m_pSpotLight->SetDiffuse(0.8f, 0.8f, 0.8f);
    m_pSpotLight->SetSpecular(0.7f, 0.7f, 0.7f);
    m_pSpotLight->SetAttenuation(1.0f, 0.0001f, 0.00001f);
    m_pSpotLight->SetPos(m_pSpaceship->GetOrientation().GetPos());
    m_pSpotLight->SetDirection(m_pStar->GetOrientation().GetPos() - m_pSpaceship->GetOrientation().GetPos());
    m_pSpotLight->SetCutoff(10.0f);
    m_pSpotLight->SetExponent(1.0f);
    m_pSpotLight->TurnOn();
}

void SolarExplorer::CreateObjects()
{
    m_pStar = m_pColossus->CreateMesh("Star", "/home/cl/hacking/graphics/models/pluto/Pluto.3ds");
    m_pStar->AddToFrame();

    m_pStarColorMap = m_pColossus->CreateTexture(COLOSSUS_TEXTURE_TYPE_2D);
    m_pStarColorMap->Load2D("/home/cl/hacking/graphics/models/venus.jpg");
    m_pStar->SetColorMap(m_pStarColorMap);

    m_pStarBumpMap = m_pColossus->CreateTexture(COLOSSUS_TEXTURE_TYPE_2D);
    m_pStarBumpMap->Load2D("/home/cl/hacking/graphics/media/stone_normal.dds");
    m_pStar->SetBumpMap(m_pStarBumpMap);

    m_pStar->GetOrientation().SetPos(-60.0f, 0.0f, 0.0f);
    m_pStar->GetOrientation().SetDirection(0.0f, 0.0f, -1.0f);
    //m_pStar->GetOrientation().SetVelocity(1.0f);

    m_pSpaceship = m_pColossus->CreateMesh("Star", "/home/cl/hacking/graphics/models/salyut7/salyut7.3ds");
    m_pSpaceship->AddToFrame();

    m_pSpaceshipColorMap = m_pColossus->CreateTexture(COLOSSUS_TEXTURE_TYPE_2D);
    m_pSpaceshipColorMap->Load2D("/home/cl/hacking/graphics/models/salyut7/salyut7solar.dds");

    m_pSpaceship->SetColorMap(m_pSpaceshipColorMap);
    m_pSpaceship->SetScale(0.05f);

    m_pSkyBoxMap = m_pColossus->CreateTexture(COLOSSUS_TEXTURE_TYPE_CUBEMAP);
    m_pSkyBoxMap->LoadCubeMap("/home/cl/hacking/graphics/models/purplenebula/purplenebula_up.jpg",
                       "/home/cl/hacking/graphics/models/purplenebula/purplenebula_dn.jpg",
                       "/home/cl/hacking/graphics/models/purplenebula/purplenebula_lf.jpg",
                       "/home/cl/hacking/graphics/models/purplenebula/purplenebula_rt.jpg",
                       "/home/cl/hacking/graphics/models/purplenebula/purplenebula_ft.jpg",
                       "/home/cl/hacking/graphics/models/purplenebula/purplenebula_bk.jpg");
    m_pColossus->SetSkyBox(m_pSpaceshipColorMap);
}

void SolarExplorer::UpdateFrame()
{
    m_spaceshipAngle += 0.25f;
    m_pSpaceship->GetOrientation().SetPos(sinf(ToRadian(m_spaceshipAngle)) * 70.0f,
                                          10.0f,
                                          cosf(ToRadian(m_spaceshipAngle)) * 70.0f);
    m_pSpotLight->SetPos(m_pSpaceship->GetOrientation().GetPos());
    m_pSpotLight->SetDirection(m_pStar->GetOrientation().GetPos() - m_pSpaceship->GetOrientation().GetPos());
}


void SolarExplorer::OnKeyboard(unsigned char Key, int x, int y)
{
    switch (Key) {
        case ' ':
            if (m_pStar->GetBumpMap()) {
                m_pStar->SetBumpMap(NULL);
            }
            else {
                m_pStar->SetBumpMap(m_pStarBumpMap);
            }
            break;

        default:
            Base3DApplication::OnKeyboard(Key, x, y);
    }
}

void SolarExplorer::OnSpecialKeys(int Key, int x, int y)
{
    m_pCurrentCamera->OnKeyboard(Key, x, y);
}


void SolarExplorer::OnPassiveMouseMov(int x, int y)
{
    m_pCurrentCamera->OnPassiveMouseMov(x, y);
}

void SolarExplorer::OnMouseMov(int x, int y)
{
    m_pCurrentCamera->OnPassiveMouseMov(x, y);
}


int main (int argc, char *argv[])
{
    try {
        SolarExplorer App(1280, 1024);
        App.Run();
    } catch (const std::string& error) {
        assert(0);
    }

    return(0);
}
