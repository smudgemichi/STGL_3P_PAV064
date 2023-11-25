#include <windows.h>
#include <string>
#include "resource.h"
#include <fstream>
#include <CommCtrl.h>
using namespace std;
HWND g_hDlgLogin;
HWND g_hEditCedula;
HWND g_hEditPassword;
HINSTANCE g_hInstance;
int ind; char seleccionado[15];
char eventosproximos[12][50] = {"Chayanne - 9/03/24", "Pimpinela - 21/05/24", "Yuridia - 2/09/24", "OV7 - 15/12/24"};
char ventaboletos[12][30] = {"Premium Chayanne", "Básico Yuridia", "VIP Pimpinela", "Premium 0V7" };
INT_PTR CALLBACK VPDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK PRDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
//INICIAR SESIÓN
INT_PTR CALLBACK LoginDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG: {
        g_hDlgLogin = hDlg;
        g_hEditCedula = GetDlgItem(hDlg, IDC_EDIT_CEDULA);
        g_hEditPassword = GetDlgItem(hDlg, IDC_EDIT_PASSWORD);
        return (INT_PTR)TRUE;
    } break;
    case WM_COMMAND: {
        if (LOWORD(wParam) == IDC_BUTTON_CONTINUE) {
            char cedula[100];
            char password[100];
            GetWindowText(g_hEditCedula, cedula, sizeof(cedula));
            GetWindowText(g_hEditPassword, password, sizeof(password));
            if (strcmp(cedula, "2071910") == 0 && strcmp(password, "12345") == 0) {
                EndDialog(hDlg, IDOK);  
                MessageBox(NULL, "Inicio de sesión exitoso", "Sesión", MB_OK | MB_ICONINFORMATION);
                DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_VP), NULL, VPDlgProc);
            }
            else {
                MessageBoxA(hDlg, "Ingreso incorrecto. Inténtalo de nuevo.", "Error", MB_OK | MB_ICONERROR);
            }
        }
        
    }break;
    case WM_CLOSE: {
        EndDialog(hDlg, IDCANCEL);
    }
    }
    return (INT_PTR)FALSE;
}
//VENTANA PRINCIPAL
INT_PTR CALLBACK VPDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG: {
        //Llenar visualización de eventos próximos
        for (int i = 0; i < 12; i++) {
            SendMessage(GetDlgItem(hDlg, IDC_LIST_EP), LB_INSERTSTRING, i, (LPARAM)eventosproximos[i]);
        }
        //Llenar venta de boletos disponibles
        for (int i = 0; i < 12; i++) {
            SendMessage(GetDlgItem(hDlg, IDC_LIST_vb), LB_INSERTSTRING, i, (LPARAM)ventaboletos[i]);
        }
    } break;
    case WM_COMMAND: {
        //Botón 2x1
        if (LOWORD(wParam) == IDC_DOSPORUNO) {
                int preciofijo = 250;
                //Comprobar existencia de elementos
                int tot; tot = SendMessage(GetDlgItem(hDlg, IDC_LIST_vb), LB_GETCOUNT, 0, 0);
                if (tot > 0) {
                    //Buscar índice de elemento
                    ind = SendDlgItemMessage(hDlg, IDC_LIST_vb, LB_GETCURSEL, 0, 0);
                    SendDlgItemMessage(hDlg, IDC_LIST_vb, LB_GETTEXT, ind, (LPARAM)seleccionado);
                    MessageBox(NULL, "Monto original: $500-->Cargo con promoción: $250.", "Promoción Aplicada: 2x1", MB_OK | MB_ICONINFORMATION);
                    MessageBox(NULL, "Aplicación de IVA: $290.", "Promoción Aplicada: 2x1", MB_OK | MB_ICONINFORMATION);
                    SendMessage(GetDlgItem(hDlg, IDC_LIST_MC), LB_INSERTSTRING, 0, (LPARAM)seleccionado);
                    SendMessage(GetDlgItem(hDlg, IDC_LIST_MC), LB_INSERTSTRING, 0, (LPARAM)seleccionado);
                } //CASO DE VACÍO
                else { MessageBox(hDlg, "No hay elementos", "ADVERTENCIA", MB_OK | MB_ICONINFORMATION); }
        }
        //Botón 10%
        if (LOWORD(wParam) == IDC_POURCENTAGE2) {
            int preciofijo = 250;
            int preciodescuentado = preciofijo - 25;
            int tot; tot = SendMessage(GetDlgItem(hDlg, IDC_LIST_vb), LB_GETCOUNT, 0, 0);
            if (tot > 0) {
                //Buscar índice de elemento
                ind = SendDlgItemMessage(hDlg, IDC_LIST_vb, LB_GETCURSEL, 0, 0);
                SendDlgItemMessage(hDlg, IDC_LIST_vb, LB_GETTEXT, ind, (LPARAM)seleccionado);
                MessageBox(NULL, "Monto original: $250-->Cargo con promoción: $225.", "Promoción Aplicada: 10%", MB_OK | MB_ICONINFORMATION);
                MessageBox(NULL, "Aplicación de IVA: $265.", "Promoción Aplicada: 10%", MB_OK | MB_ICONINFORMATION);
                SendMessage(GetDlgItem(hDlg, IDC_LIST_MC), LB_INSERTSTRING, 0, (LPARAM)seleccionado);
            } //CASO DE VACÍO
            else { MessageBox(hDlg, "No hay elementos", "ADVERTENCIA", MB_OK | MB_ICONINFORMATION); }
        }
        //Botón salir
        if (LOWORD(wParam) == ID_OPCIONES_SALIR) {
            EndDialog(hDlg, IDCANCEL);
        }
    } break;
    case WM_CLOSE: {
        EndDialog(hDlg, IDCANCEL);
    }
    }
    return (INT_PTR)FALSE;
}
//**PROGRAMA**
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_LOGIN), NULL, LoginDlgProc);
    return 0;
}