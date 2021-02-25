#include <Arduboy2.h>

void title_Init() {

    gameState = GameState::Title;
    arduboy.resetFrameCount();

    clearLEDs();

    #ifdef ARDUBOY_TONES_SOUNDS
        sound.tones(Sounds::Score);
    #endif

}   

void title() {

    Sprites::drawOverwrite(0, 0, Images::Title_00, 0);
    Sprites::drawOverwrite(73, 13, Images::Title_01, 0);
    Sprites::drawOverwrite(51, 46, Images::Title_01, 0);

    uint8_t frameCount = arduboy.getFrameCount(192);

    Sprites::drawOverwrite(5, 17, Images::Title_02, 0);
    
    #ifdef FLICKERING
        switch (frameCount) {

            case 0:
            case 1:
            case 5:
            case 7:
            case 16:
            case 61:
                arduboy.fillRect(0, 17, WIDTH, 24, BLACK);
                break;

            case 64 ... 65:            
                arduboy.fillRect(0, 17, WIDTH, 3, BLACK);
                break;

            case 66:
            case 75:
                arduboy.fillRect(0, 33, WIDTH, 5, BLACK);
                break;

            case 69 ... 70:       
                arduboy.fillRect(0, 22, WIDTH, 8, BLACK);
                break;

            case 132:       
            case 136:       
                arduboy.drawFastHLine(0, 24, 40, BLACK);
                arduboy.drawFastHLine(30, 34, 50, BLACK);
                arduboy.drawFastHLine(60, 42, 50, BLACK);
                break;

            case 134:       
                arduboy.drawFastHLine(60, 24, 40, BLACK);
                arduboy.drawFastHLine(30, 34, 50, BLACK);
                arduboy.drawFastHLine(0, 42, 50, BLACK);
                break;

            default:
                break;
                
        }
    #endif

    arduboy.fillRect(20, 4, WIDTH, 4, WHITE);
    arduboy.drawFastHLine(0, 13, 73);
    arduboy.drawFastHLine(13, 9, WIDTH);
    arduboy.drawFastHLine(55, 46, WIDTH);
    arduboy.drawFastHLine(0, 50, 25);
    arduboy.fillRect(0, 52, 25, 4, WHITE);
    arduboy.drawRect(25, 50, 77, 11);
    font3x5.setCursor(29, 52);

    if (arduboy.getFrameCountHalf(254)) {
        font3x5.print(F("PRESS~'A'~TO~BREACH"));
    }
    else {
        font3x5.print(F("HOLD   ~BOOTLOADER")); 
        Sprites::drawSelfMasked(46, 53, Images::UpDown, 0);
    }

    Sprites::drawSelfMasked(51, 46, Images::Title_01, 0);

    if (arduboy.justPressed(A_BUTTON)) { 

        player.reset();
        mapGameVars.setMessage(Message::Intro_1);

        gameState = GameState::Message_Intro_Init;

        #ifdef ARDUBOY_TONES_SOUNDS
            sound.noTone();
        #endif

        #ifdef BYTE_BEAT_SOUNDS
            enableByteBeat();
        #endif

    }

}
