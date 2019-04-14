//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream.h>
#include <windows.h>
#include <fstream.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
WIN32_FIND_DATA fattrs;	
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool DeleteDir(AnsiString DirName)
{
TSearchRec sr;
if (DirName.Length())
 {
 if (!FindFirst(DirName+"\\*.*",faAnyFile,sr))
 do
  {
  if (!(sr.Name=="." || sr.Name==".."))
   if (((sr.Attr & faDirectory) == faDirectory ) ||(sr.Attr == faDirectory))
    {
    FileSetAttr(DirName+"\\"+sr.Name, faDirectory );
    DeleteDir(DirName+"\\"+sr.Name);
    RemoveDir(DirName + "\\"+sr.Name);
    }
    else
    {
    FileSetAttr(DirName+"\\"+sr.Name, 0);
    DeleteFile(DirName+"\\"+sr.Name);
    }
  }
 while (!FindNext(sr));
 FindClose(sr);
 }
RemoveDir(DirName);
return true;
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
//-----------------------------------------------------------------------------------------------------//
 if (!CreateDirectory("C:\\Zakharov\\temp",NULL))   // ÑÒÂÎÐÞªÌÎ ÄÅÐÈÊÒÎÐ²Þ
                if (DeleteDir("C:\\Zakharov\\temp")){// ßÊÙÎ ÍÅ ÑÒÂÎÐÞªÒÜÑß, ÇÍÀ×ÈÒÜ ÂÎÍÀ ÂÆÅ ª -- ÂÈÄÀËßªÌÎ ÒÀ ÑÒÂÎÐÞªÌÎ ÇÍÎÂÓ
                        CreateDirectory("C:\\Zakharov\\temp",NULL);
                               }

//-----------------------------------------------------------------------------------------------------//
int N = UpDown1->Position;
int K = UpDown2->Position;
int LineCounter = 0;
string line, inputFile;
inputFile = "C:\\Zakharov\\infile.txt";
if (Edit3->Text.IsEmpty()){inputFile = Edit3->Text.c_str();}
std::ifstream in(inputFile.c_str()); // îêðûâàåì ôàéë äëÿ ÷òåíèÿ
std::ofstream of("C:\\Zakharov\\temp\\outfile.txt");
std::ofstream ofDirectory("C:\\Zakharov\\temp\\outfileDirectory.txt");

if (in.is_open()&& of.is_open())
        {
                while (getline(in, line))
                {
                        LineCounter++;
                        if (LineCounter>N && K > LineCounter)
                        {
                                of << line;
                                of <<'\n';
                        }
                }
        }
in.close();     // çàêðûâàåì ôàéë
of.close();
//-----------------------------------------------------------------------------------------------------//
        AnsiString str;
       WIN32_FIND_DATA winFileData;
            HANDLE hFile;
            char szPath[MAX_PATH];

                        hFile = FindFirstFile("C:\\WINDOWS\\Help\\*.*",&winFileData);
                        if (hFile!=INVALID_HANDLE_VALUE && ofDirectory.is_open())
                        {
                                   do
                                   {
                                       ofDirectory << winFileData.cFileName;
                                       ofDirectory <<'\n';
                                   }
                                   while (FindNextFile(hFile,&winFileData)!=0);
                                   FindClose(hFile);
                        }

        ofDirectory.close();

 }
//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
        Edit1->Text = UpDown1->Position;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::UpDown2Click(TObject *Sender, TUDBtnType Button)
{
        Edit2->Text = UpDown2->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
   UpDown2->Position  = StrToInt(Edit2->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
    UpDown1->Position  = StrToInt(Edit1->Text);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::N2Click(TObject *Sender)
{
 if(OpenDialog1->Execute()){
        Edit3->Text = OpenDialog1->FileName;
 }
}
//---------------------------------------------------------------------------

