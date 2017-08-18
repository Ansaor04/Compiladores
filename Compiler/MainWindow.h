#pragma once
#include "FSM.h"
#include <msclr\marshal_cppstd.h>

CFSM FSM;

namespace Compiler {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
			


	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  compileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  compileProgramToolStripMenuItem;
	private: System::Windows::Forms::Label^  label1;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compileProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 31);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(968, 410);
			this->textBox1->TabIndex = 0;
			this->textBox1->ScrollBars = ScrollBars::Vertical;
			this->textBox1->AcceptsTab = true;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuItem1,
					this->compileToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(992, 28);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->saveToolStripMenuItem,
					this->loadToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(44, 24);
			this->toolStripMenuItem1->Text = L"File";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(117, 26);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::saveToolStripMenuItem_Click);
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(117, 26);
			this->loadToolStripMenuItem->Text = L"Load";
			this->loadToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::loadToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(117, 26);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::exitToolStripMenuItem_Click);
			// 
			// compileToolStripMenuItem
			// 
			this->compileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->compileProgramToolStripMenuItem });
			this->compileToolStripMenuItem->Name = L"compileToolStripMenuItem";
			this->compileToolStripMenuItem->Size = System::Drawing::Size(77, 24);
			this->compileToolStripMenuItem->Text = L"Compile";
			// 
			// compileProgramToolStripMenuItem
			// 
			this->compileProgramToolStripMenuItem->Name = L"compileProgramToolStripMenuItem";
			this->compileProgramToolStripMenuItem->Size = System::Drawing::Size(202, 26);
			this->compileProgramToolStripMenuItem->Text = L"Compile program";
			this->compileProgramToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::compileProgramToolStripMenuItem_Click);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->textBox2->Location = System::Drawing::Point(13, 463);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(966, 212);
			this->textBox2->TabIndex = 2;
			this->textBox2->ScrollBars = ScrollBars::Vertical;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 687);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(49, 17);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Ready";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(992, 713);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainWindow";
			this->Text = L"Compiler V0.3";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		
	}
	private: System::Void loadToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void compileProgramToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		System::String^ managedString = this->textBox1->Text;
		msclr::interop::marshal_context context;

		std::string Str = context.marshal_as<std::string>(managedString);

		static unsigned short sCompiledTimes = 0;

		FSM.reset();

		//lexic
		FSM.setMode(CompilerPhase::E::lexic);
		FSM.pChar = &Str[0];
		while (FSM.pChar != &Str[Str.size()])
			FSM.update();

		//syntactic
		FSM.setMode(CompilerPhase::E::syntactic);
		FSM.Syn->processTokens();


		//semantic
		if (!FSM.bHasErrors)
		{
			FSM.setMode(CompilerPhase::E::semantic);
			FSM.Sem->checkTokens();
		}
		else
			FSM.pushError(SynE::E::custom, "Errors found, no semantic check could be done.");

		FSM.closeFile();
		
		if (sCompiledTimes == 0)
			this->label1->Text = "Compiled";
		else
			this->label1->Text = "Compiled (" + sCompiledTimes + ")";

		if (FSM.bHasErrors)
		{
			std::ifstream iErr(FSM.filename + ".err");
			std::string Errors((std::istreambuf_iterator<char>(iErr)), std::istreambuf_iterator<char>());
			String^ managedError = gcnew String(Errors.c_str());

			if(FSM.Syn->iRecoveredErrors != 0)
				this->textBox2->Text = managedError + "Compiler recovered from " + FSM.Syn->iRecoveredErrors + " syntactic errors";
			else
				this->textBox2->Text = managedError;
		}
		else
			this->textBox2->Text = "All Done, No compiler errors found";

		sCompiledTimes++;
	}
};
}