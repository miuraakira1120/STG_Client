#include "TitleScene.h"
#include"Engine/Camera.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "resource.h"
#include "UDPClient.h"

HINSTANCE hInst;

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("matchingStay.jpg");
	assert(hPict_ >= 0);
}

//更新
void TitleScene::Update()
{
	if (UDPClient::GetIsStart())
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void TitleScene::Release()
{
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

// このコード モジュールに含まれる関数の宣言を転送します:
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int  nCmdShow)
{
    hInst = hInstance;
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
    return (int)0;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    HWND hMessageEdit = GetDlgItem(hDlg, IDD_DIALOG1);
    switch (msg) {
    case IDC_IPADDRESS1:
       /* switch (LOWORD(wp)) {
        case IDC_SENDBUTTON:
            message += L"aaa\r\n";
            SetWindowText(hMessageEdit, message.c_str());
            return TRUE;
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }*/
        return FALSE;
    case IDC_EDIT1:
        return TRUE;
    }

    return FALSE;
}
//
////ダイアログ
//BOOL TitleScene::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
//{
//    switch (msg)
//    {
//    case IDC_IPADDRESS1:
//        //SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
//
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"1-デフォルト");//ダイアログ文字表示
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"2-レンガ");
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"3-草");
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"4-水");
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"5-砂");
//
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_SETCURSEL, 0, 0);//最初に表示する文字
//
//        return TRUE;
//    case IDC_EDIT1:
//       /* switch (LOWORD(wp))
//        {
//        case IDC_RADIO_UP:
//            mode_ = 0;
//            return TRUE;
//        case IDC_RADIO_DOWN:
//            mode_ = 1;
//            return TRUE;
//        case IDC_RADIO_CHANGE:
//            mode_ = 2;
//            return TRUE;
//        case IDC_COMBO_TYPE:
//            select_ = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_GETCURSEL, 0, 0);
//            return TRUE;
//        default:
//            break;
//        }*/
//        return TRUE;
//    }
//    return FALSE;
//}