#include "XuLyChung.h"
#include "MainObject.h"
#include "AmoObject.h"
#include "ThreatObject.h"
#include "VuNo.h"
#include "Player.h"
#include "Text.h"
#include "TySoFPS.h"

using namespace std;

TTF_Font* g_font_text = NULL;
TTF_Font* g_font_text_menu = NULL;

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
	{
		return false;
	}

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT,2, 4096)== -1)
	{
		return false;
	}

	//READ FILE AUDIO
	g_sound_amo = Mix_LoadWAV(g_name_audio_amo_main);
	g_sound_VuNo[0] = Mix_LoadWAV(g_name_audio_vuno_main);
	g_sound_VuNo[1] = Mix_LoadWAV(g_nam_audio_vuno_threats);
	g_sound_bgr = Mix_LoadWAV(g_name_audio_background);
	g_sound_over = Mix_LoadWAV(g_name_audio_over);
	g_sound_intro = Mix_LoadWAV(g_name_audio_intro);

	if(g_sound_amo == NULL || g_sound_VuNo[0] == NULL || g_sound_VuNo[1] == NULL || g_sound_bgr == NULL || g_sound_over == NULL || g_sound_intro == NULL)
	{
		return false;
	}

	if(TTF_Init() == -1)
	{
		return false;
	}

	g_font_text = TTF_OpenFont("text.ttf", 20);
	g_font_text_menu = TTF_OpenFont("text.ttf", 50);

	if(g_font_text == NULL || g_font_text_menu == NULL)
	{
		return false;
	}
	return true;
}

int main(int arc, char* argv[])
{
	TySoFPS fps_timer;

	int bgr=0;
	bool is_quit = false;
	if (!Init())
	{
		return 0;
	}

	g_bkground = SDLxulychung::LoadImage(g_name_bgr);
	if (g_bkground == NULL)
	{
		return 0;
	}

	
	//MAKE PLAYER TURN
	Player player_turn;
	player_turn.Init1();

	//MAKE HP_MAIN
	Player Main_hp;
	Main_hp.Init2();

	//MAKE MARK
	Text score;
	score.SetColor(Text::WHITE_TEXT);

	//MAKE HP_MAIN
	Text Hp;
	Hp.SetColor(Text::WHITE_TEXT);

	//make MainObject
	MainObject plane_object;
	plane_object.setRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
	bool ret= plane_object.LoadImg(g_name_main_obj); 
	if(!ret)
	{
		return 0;
	}

	//Init VuNoObject
	VuNo Vu_No;

	ret = Vu_No.LoadImg(g_name_vuno);
	Vu_No.set_clip();
	if(ret == false)
	{
		return 0;
	}

	//makeThreatObject
	ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
	for(int j=0; j< NUM_THREATS; j++)
	{
		 ThreatObject* p_threat = (p_threats + j);
		if(p_threat)
		{
			ret = p_threat->LoadImg(g_name_threats);
			if(ret == false)
			{
				delete[] p_threats;
				SDLxulychung::CleanUp();
				SDL_Quit();
				return 0;
			}
		    int rand_x = SDLxulychung::MakeRandValue();
			p_threat->setRect(rand_x, 0-j*VAL_OFFSET_START_POST_THREATS);
			p_threat->set_y_val(SPEED_THREAT); //SET TOC DO CUA THREATS

			AmoObject* p_amo = new AmoObject();
			p_threat->InitAmo(p_amo);
		}
		
	}
	unsigned int die_number = 0;
	unsigned int Accident = 0;
	unsigned int score_val = 0;

	Mix_HaltChannel(-1);
	Mix_PlayChannel(0, g_sound_intro, -1);
	int ret_menu_intro = SDLxulychung::ShowMenuIntro(g_screen, g_font_text_menu);
	if(ret_menu_intro == 1)
	{
		is_quit=true;
	}

	Mix_HaltChannel(-1);
	//show music background
	Mix_PlayChannel(0, g_sound_bgr, -1);
	while (!is_quit) 
	{
		fps_timer.start();
		while (SDL_PollEvent(&g_even)) 
		{		
			if (g_even.type == SDL_QUIT)
			{			
				is_quit = true;
				break;
			}			
			plane_object.HandleInputAction(g_even, g_sound_amo);
		}

		//apply background
		bgr += SPEED_SCREEN;
		SDLxulychung::ApplySurface(g_bkground, g_screen, 0, bgr);
		SDLxulychung::ApplySurface(g_bkground, g_screen, 0 , bgr-SCREEN_HEIGHT);
		if(bgr>= SCREEN_HEIGHT)
		{
			bgr = 0;
		}
		
		//Show player turn
		player_turn.Render(g_screen);
		//show main_hp
		Main_hp.Render(g_screen);

		//Implement mainObject
		plane_object.HandleMove();
		plane_object.Show(g_screen);
		plane_object.MakeAmo(g_screen);

       //Implement threatObject
		for(int k=0; k< NUM_THREATS; k++)
		{
			ThreatObject* p_threat = (p_threats+k);
			if(p_threat)
			{
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

				//VA CHAM THREAT AMO -> MAIN OBJECT
				bool is_vacham1 = false;
				vector<AmoObject*> amo_arr = p_threat->GetAmoList();
				for (int am = 0; am < amo_arr.size(); am++)
				{
					AmoObject* p_amo = amo_arr.at(am);
					if (p_amo)
					{
						is_vacham1 = SDLxulychung::CheckVaCham(p_amo->GetRect(), plane_object.GetRect());
						if (is_vacham1 == true)
						{
							p_threat->ResetAmo(p_amo);
							break;
						}
					}
				}

				//CHECK VA CHAM GIUA MAIN VOI THREATS
				bool is_VaCham = SDLxulychung::CheckVaCham(plane_object.GetRect(), p_threat->GetRect());
				if (is_vacham1 || is_VaCham)
				{
					for (int ex = 0; ex < NUMBER_FRAME; ex++)
					{
						int x_pos = (plane_object.GetRect().x+ plane_object.GetRect().w*0.5)-VUNO_WIDTH*1.5/3 ;
						int y_pos = (plane_object.GetRect().y+ plane_object.GetRect().h*0.5)-VUNO_HEIGHT*0.7/3 ;

						Vu_No.set_frame(ex);
						Vu_No.setRect(x_pos, y_pos);
						Vu_No.showVuNo(g_screen);
						//Update screen
						if ( SDL_Flip(g_screen) == -1)
						{
							delete [] p_threats;
							SDLxulychung::CleanUp();
							SDL_Quit();
							return 0;
						}		
					}

					Mix_PlayChannel(-1, g_sound_VuNo[1], 0);
					
					
					Accident++;
					if(Accident<=4)
					{						
						Main_hp.Decrease(); 
						Main_hp.Render(g_screen);
						if (SDL_Flip(g_screen) == -1)
						{
							delete [] p_threats;
							SDLxulychung::CleanUp();
							SDL_Quit();
							return 0;
						}					
					}
					else 
					{
						die_number++;
						if(die_number<=2)
						{				
							SDL_Delay(DELAY_COMEBACK);	
							plane_object.setRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
							player_turn.Decrease();
							player_turn.Render(g_screen);
							Main_hp.Init2();
							if (SDL_Flip(g_screen) == -1)
							{
								delete [] p_threats;
								SDLxulychung::CleanUp();
								SDL_Quit();
								return 0;
							}
						}		
						else
						{
							Mix_HaltChannel(-1);
							Mix_PlayChannel(-1, g_sound_over, 0);
							int ret_menu_over = SDLxulychung::ShowMenuOver(g_screen, g_font_text_menu);
							if(ret_menu_over == 1)
							{
								is_quit=true;
								delete [] p_threats;
								SDLxulychung::CleanUp();
								SDL_Quit();
								return 1;
							}
							/*if (MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)
							{
							delete [] p_threats;
							SDLxulychung::CleanUp();
							SDL_Quit();
							return 1;
							}*/
						}
					}
				}

				//CHECK VA CHAM GIUA MAIN AMO VOI THREATS
				vector<AmoObject*> amo_list = plane_object.GetAmoList();
				for (int im = 0; im < amo_list.size(); im++)
				{
					AmoObject* p_amo = amo_list.at(im);
					if (p_amo != NULL)
					{
						bool ret_VaCham = SDLxulychung::CheckVaCham(p_amo->GetRect(), p_threat->GetRect());
						if (ret_VaCham)
						{
							score_val ++;
							for (int tx = 0; tx < 4; tx++)
							{
								int x_pos = p_amo->GetRect().x - VUNO_WIDTH*0.5;
								int y_pos = p_amo->GetRect().y - VUNO_HEIGHT*0.1;
								/*int x_pos = (p_threat->GetRect().x+ p_threat->GetRect().w*0.5-VUNO_WIDTH*0.4);
								int y_pos = (p_threat->GetRect().y+ p_threat->GetRect().h*0.5-VUNO_HEIGHT*0.1);*/

								Vu_No.set_frame(tx);
								Vu_No.setRect(x_pos, y_pos);
								Vu_No.showVuNo(g_screen);
								/*SDL_Delay(5);*/
								//UPDATE SCREEN
								if (SDL_Flip(g_screen) == -1)
								{
									delete [] p_threats;
									SDLxulychung::CleanUp();
									SDL_Quit();
									return 0;
								}
							}
							p_threat->Reset(0-k*VAL_OFFSET_START_POST_THREATS);
 							plane_object.RemoveAmo(im);
							Mix_PlayChannel(-1, g_sound_VuNo[0], 0);
						}
					}
				}
				
				////check VaCham: plane_object vs threats_object
				//bool is_VaCham = SDLxulychung::CheckVaCham(plane_object.GetRect(), p_threat->GetRect());
				//if(is_VaCham)
				//{
				//	for(int ex=0; ex<4 ; ex++)
				//	{
				//		int x_pos = (plane_object.GetRect().x+ plane_object.GetRect().w*0.5)-VUNO_WIDTH*1.5/3 ;
				//		int y_pos = (plane_object.GetRect().y+ plane_object.GetRect().h*0.5)-VUNO_HEIGHT*0.7/3 ;

				//		Vu_No.set_frame(ex);
				//		Vu_No.setRect(x_pos, y_pos);
				//		Vu_No.showVuNo(g_screen);
				//		Mix_PlayChannel(-1, g_sound_VuNo[1], 0);
				//		if ( SDL_Flip(g_screen) == -1)
				//		{
				//			delete[] p_threats;
				//			SDLxulychung::CleanUp();
				//			SDL_Quit();
				//			return 0;
				//		}
				//	if(MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK)== IDOK)
				//	{
				//		delete[] p_threats;
				//		SDLxulychung::CleanUp();
				//		SDL_Quit();
				//		return 1;
				//	}
				//}
				//}
				
				//// check VaCham: bullet of threat_object vs plane_object
				//std::vector<AmoObject*> amo_list2 = p_threat->GetAmoList();
				//for(int jm = 0; jm < amo_list2.size(); jm++)
				//{
				//	AmoObject* p_amo = amo_list2.at(jm);
				//	if(p_amo != NULL)
				//	{			
				//		bool ret_VaCham = SDLxulychung::CheckVaCham(p_amo->GetRect(), plane_object.GetRect());
				//		if(ret_VaCham)
				//		{
				//			for(int ex=0; ex<4 ; ex++)
				//			{
				//				int x_pos = (plane_object.GetRect().x+ plane_object.GetRect().w*0.5-VUNO_WIDTH*1.5/3) ;
				//				int y_pos = (plane_object.GetRect().y+ plane_object.GetRect().h*0.5-VUNO_HEIGHT*0.7/3) ;

				//				Vu_No.set_frame(ex);
				//				Vu_No.setRect(x_pos, y_pos);
				//				Vu_No.showVuNo(g_screen);
				//				//SDL_Delay(200);
				//				if ( SDL_Flip(g_screen) == -1)
				//				{
				//					delete[] p_threats;
				//					SDLxulychung::CleanUp();
				//					SDL_Quit();
				//					return 0;
				//				}
				//				Mix_PlayChannel(-1, g_sound_VuNo[1], 0);
				//			}
				//			if(MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK)== IDOK)
				//			{
				//				delete[] p_threats;
				//				SDLxulychung::CleanUp();
				//				SDL_Quit();
				//				return 1;
				//			}
				//		}
				//	}
				//}

				////check VaCham: threats vs bullet of plane_object
				//std::vector<AmoObject*> amo_list = plane_object.GetAmoList();
				//for(int im = 0; im < amo_list.size(); im++)
				//{
				//	AmoObject* p_amo = amo_list.at(im);
				//	if(p_amo != NULL)
				//	{
				//		bool ret_VaCham = SDLxulychung::CheckVaCham(p_amo->GetRect(), p_threat->GetRect());
				//		if(ret_VaCham)
				//		{
				//			for(int ex=0; ex<4 ; ex++)
				//			{
				//				int x_pos = (p_threat->GetRect().x+ p_threat->GetRect().w*0.5-VUNO_WIDTH*0.4);
				//				int y_pos = (p_threat->GetRect().y+ p_threat->GetRect().h*0.5-VUNO_HEIGHT*0.1);

				//				Vu_No.set_frame(ex);
				//				Vu_No.setRect(x_pos, y_pos);
				//				Vu_No.showVuNo(g_screen);
				//				if ( SDL_Flip(g_screen) == -1)
				//				{
				//					delete[] p_threats;
				//					SDLxulychung::CleanUp();
				//					SDL_Quit();
				//					return 0;
				//				}
				//			}
				//			p_threat->Reset(0-k*400);
				//			plane_object.RemoveAmo(im);
				//			Mix_PlayChannel(-1, g_sound_VuNo[0], 0);
				//		}
				//	}
				//}
			}
		}

		//SHOW HP_MAIN
		string str_Hp = "HP:";
		Hp.SetText(str_Hp);
		Hp.setRect(430, 7);
		Hp.CreatGameText(g_font_text, g_screen);

		//SHOW MARK_VALUE TO SCREEN
		string val_str_score = to_string(score_val);
		string strScore("SCORE: ");
		strScore += val_str_score;

		score.SetText(strScore);
		score.CreatGameText(g_font_text, g_screen);

		//update screen
		if ( SDL_Flip(g_screen) == -1)
		{
			delete[] p_threats;
			SDLxulychung::CleanUp();
			SDL_Quit();
			return 0;
		}

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000/FRAME_PER_SECOND;

		if(real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time>=0)
			SDL_Delay(delay_time);
		}
	}

   	delete[] p_threats;
   	SDLxulychung::CleanUp();
   	SDL_Quit();
   	return 1;
}