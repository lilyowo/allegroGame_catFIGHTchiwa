// [main.c]
// this template is provided for the 2D shooter game.

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>


// If defined, logs will be shown on console and written to file.
// If commented out, logs will not be shown nor be saved.
#define LOG_ENABLED

/* Constants. */

// Frame rate (frame per second)
const int FPS = 60;
// Display (screen) width.
const int SCREEN_W = 1000;
// Display (screen) height.
const int SCREEN_H = 600;
// At most 10 audios can be played at a time.
const int RESERVE_SAMPLES = 10;
// Same as:
// const int SCENE_MENU = 1;
// const int SCENE_START = 2;
enum {
    SCENE_MENU = 1,
    SCENE_START = 2,
    // [HACKATHON 3-7]
    // TODO: Declare a new scene id.
    SCENE_SETTINGS = 3,
    SCENE_GEME_OVER = 4,
    SCENE_WIN = 5,
    SCENE_SELECT =6,
    SCENE_ANIMATE =7,
    SCENE_SKILL =8,
    SCENE_RULE =9
};
//owo score board
char score_text[10];
char hp_text[10];
char cans_text[10];
//owo hidden role
int win_time=1;
char win_time_text[10];

int score=0;
//owo setting board
int chiattackblood = 1;
int canvx = 10;
int bossswordvy = 5;
int enemyblood = 50;
//owo select char
int select_char=1;
//owo boss music
int bossbgmflag=1;
int little_flag=1;
//owo sound icon
int all_sound = 1;
int bullet_sound = 1;
//1 black cat 2 white cat
/* Input states */

// The active scene id.
int active_scene;
//owo 新子彈
int new_bullet_flag=0;
// Keyboard state, whether the key is down or not.
bool key_state[ALLEGRO_KEY_MAX];
// Mouse state, whether the key is down or not.
// 1 is for left, 2 is for right, 3 is for middle.
bool *mouse_state;
// Mouse position.
int mouse_x, mouse_y;
// TODO: More variables to store input states such as joysticks, ...

/* Variables for allegro basic routines. */

ALLEGRO_DISPLAY* game_display;
ALLEGRO_EVENT_QUEUE* game_event_queue;
ALLEGRO_TIMER* game_update_timer;

/* Shared resources*/

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
//owo score board
ALLEGRO_FONT* font_score;
// TODO: More shared resources or data that needed to be accessed
// across different scenes.

/* Menu Scene resources*/
ALLEGRO_BITMAP* main_img_background;
// [HACKATHON 3-1]
// TODO: Declare 2 variables for storing settings images.
// Uncomment and fill in the code below.
ALLEGRO_BITMAP* img_settings;
ALLEGRO_BITMAP* img_settings2;
//owo game over
ALLEGRO_BITMAP* img_game_over;
ALLEGRO_SAMPLE* game_over_bgm;
ALLEGRO_SAMPLE_ID game_over_bgm_id;
//owo winning
ALLEGRO_BITMAP* img_winning;
ALLEGRO_SAMPLE* winning_bgm;
ALLEGRO_SAMPLE_ID winning_bgm_id;


ALLEGRO_SAMPLE* main_bgm;
ALLEGRO_SAMPLE_ID main_bgm_id;



/* Start Scene resources*/
ALLEGRO_BITMAP* start_img_background;
ALLEGRO_BITMAP* start_img_plane;
ALLEGRO_BITMAP* start_img_enemy;
ALLEGRO_SAMPLE* start_bgm;
ALLEGRO_SAMPLE_ID start_bgm_id;
// [HACKATHON 2-1]
// TODO: Declare a variable to store your bullet's image.
// Uncomment and fill in the code below.
ALLEGRO_BITMAP* img_bullet;
//owo
ALLEGRO_BITMAP* img_chiwa_attack;
ALLEGRO_BITMAP* img_angle;
ALLEGRO_BITMAP* img_can;
ALLEGRO_BITMAP* img_boss;
ALLEGRO_BITMAP* img_boss_sword;
ALLEGRO_BITMAP* img_setting_bg;
ALLEGRO_BITMAP* img_new_bullet;
//owo setting
ALLEGRO_SAMPLE* setting_bgm;
ALLEGRO_SAMPLE_ID setting_bgm_id;
//owo select char
ALLEGRO_BITMAP* setting_01;
ALLEGRO_BITMAP* setting_01_1;
ALLEGRO_BITMAP* setting_02;
ALLEGRO_BITMAP* setting_02_1;
ALLEGRO_SAMPLE* select_bgm;
ALLEGRO_SAMPLE_ID* select_bgm_id;
ALLEGRO_BITMAP* select_bg;
ALLEGRO_BITMAP* img_plane2;
//owo skill
ALLEGRO_BITMAP* img_skill_bg;
ALLEGRO_SAMPLE* skill_bgm;
ALLEGRO_SAMPLE_ID skill_bgm_id;
ALLEGRO_SAMPLE* rule_bgm;
ALLEGRO_SAMPLE_ID rule_bgm_id;
ALLEGRO_BITMAP* rule_bg;
//owo bullet sound
ALLEGRO_SAMPLE* bullet_sound01;
ALLEGRO_SAMPLE_ID bullet_sound01_id;
ALLEGRO_SAMPLE* bullet_sound02;
ALLEGRO_SAMPLE_ID bullet_sound02_id;
//owo click sound
ALLEGRO_SAMPLE* click_sound;
ALLEGRO_SAMPLE_ID click_sound_id;
//owo restart
ALLEGRO_BITMAP* img_restart01;
ALLEGRO_BITMAP* img_restart02;
//owo setting board
ALLEGRO_BITMAP* img_chose_char_btm;
ALLEGRO_BITMAP* img_chose_char_btm01;
ALLEGRO_BITMAP* img_simple;
ALLEGRO_BITMAP* img_simple01;
ALLEGRO_BITMAP* img_hard;
ALLEGRO_BITMAP* img_hard01;
ALLEGRO_BITMAP* img_skill;
ALLEGRO_BITMAP* img_skill01;
//owo boss music
ALLEGRO_SAMPLE* boss_bgm;
ALLEGRO_SAMPLE_ID boss_bgm_id;
//owo sound icon
ALLEGRO_BITMAP* sound_icon01;
ALLEGRO_BITMAP* sound_icon01_1;
ALLEGRO_BITMAP* sound_icon02;
ALLEGRO_BITMAP* sound_icon02_1;
//owo hidden role
ALLEGRO_BITMAP* img_level_5_unlock;
ALLEGRO_BITMAP* img_level_10_unlock;
ALLEGRO_BITMAP* img_strong_cat_btm01;
ALLEGRO_BITMAP* img_strong_cat_btm02;
ALLEGRO_BITMAP* img_super_cat_btm01;
ALLEGRO_BITMAP* img_super_cat_btm02;
//owo sound new add
ALLEGRO_SAMPLE* enter_sound;
ALLEGRO_SAMPLE_ID* enter_sound_id;
ALLEGRO_SAMPLE* backspace_sound;
ALLEGRO_SAMPLE_ID* backspace_sound_id;
ALLEGRO_SAMPLE* heal_sound;
ALLEGRO_SAMPLE_ID* heal_sound_id;
ALLEGRO_SAMPLE* beat_sound;
ALLEGRO_SAMPLE_ID* beat_sound_id;
ALLEGRO_SAMPLE* big_knife_sound;
ALLEGRO_SAMPLE_ID* big_knife_sound_id;





typedef struct {
    // The center coordinate of the image.
    float x, y;
    // The width and height of the object.
    float w, h;
    // The velocity in x, y axes.
    float vx, vy;
    // Should we draw this object on the screen.
    bool hidden;
    // The pointer to the object’s image.
    ALLEGRO_BITMAP* img;
    //blood
    int blood;
    //cat=1,chiwa=2,paw=3
    int type;
} MovableObject;
void draw_movable_object(MovableObject obj);
#define MAX_ENEMY 5
// [HACKATHON 2-2]
// TODO: Declare the max bullet count that will show on screen.
// You can try max 4 bullets here and see if you needed more.
// Uncomment and fill in the code below.
#define MAX_BULLET 4
//owo
#define MAX_CHIWA_ATTACK 20
#define MAX_CAN 1
#define MAX_BOSS_SWORD 1
#define MAX_NEW_BULLET 10
#define TOTAL_CHAR 2

MovableObject plane;
//owo select char
MovableObject new_plane;
MovableObject enemies[MAX_ENEMY];
MovableObject angle;
// [HACKATHON 2-3]
// TODO: Declare an array to store bullets with size of max bullet count.
// Uncomment and fill in the code below.
MovableObject bullets[MAX_BULLET];
//owo
MovableObject chiwa_attack[MAX_CHIWA_ATTACK];
MovableObject can[MAX_CAN];
MovableObject boss;
MovableObject boss_sword[MAX_BOSS_SWORD];
MovableObject new_bullet[MAX_NEW_BULLET];


// [HACKATHON 2-4]
// TODO: Set up bullet shooting cool-down variables.
// 1) Declare your shooting cool-down time as constant. (0.2f will be nice)
// 2) Declare your last shoot timestamp.
// Uncomment and fill in the code below.
const float MAX_COOLDOWN = 0.2f;
double last_shoot_timestamp;
//owo
const float MAX_CHIWA_COOLDOWN = 0.2f;
double chiwa_last_shoot_timestamp;

const float MAX_CAN_COOLDOWN = 0.2f;
double can_last_shoot_timestamp;

const float MAX_BOSS_SWORD_COOLDOWN = 0.2f*5;
double boss_sword_last_shoot_timestamp;

const float MAX_NEW_BULLET_COOLDOWN = 0.2f/2;
double new_bullet_last_shoot_timestamp;


/* Declare function prototypes. */

// Initialize allegro5 library
void allegro5_init(void);
// Initialize variables and resources.
// Allows the game to perform any initialization it needs before
// starting to run.
void game_init(void);
// Process events inside the event queue using an infinity loop.
void game_start_event_loop(void);
// Run game logic such as updating the world, checking for collision,
// switching scenes and so on.
// This is called when the game should update its logic.
void game_update(void);
// Draw to display.
// This is called when the game should draw itself.
void game_draw(void);
// Release resources.
// Free the pointers we allocated.
void game_destroy(void);
// Function to change from one scene to another.
void game_change_scene(int next_scene);
// Load resized bitmap and check if failed.
ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h);
// [HACKATHON 3-2]
// TODO: Declare a function.
// Determines whether the point (px, py) is in rect (x, y, w, h).
// Uncomment the code below.
bool pnt_in_rect(int px, int py, int x, int y, int w, int h);

/* Event callbacks. */
void on_key_down(int keycode);
void on_mouse_down(int btn, int x, int y);

/* Declare function prototypes for debugging. */

// Display error message and exit the program, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// If the program crashes unexpectedly, you can inspect "log.txt" for
// further information.
void game_abort(const char* format, ...);
// Log events for later debugging, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// You can inspect "log.txt" for logs in the last run.
void game_log(const char* format, ...);
// Log using va_list.
void game_vlog(const char* format, va_list arg);

int main(int argc, char** argv) {
    // Set random seed for better random outcome.
    srand(time(NULL));
    allegro5_init();
    game_log("Allegro5 initialized");
    game_log("Game begin");
    // Initialize game variables.
    game_init();
    game_log("Game initialized");
    // Draw the first frame.
    game_draw();
    game_log("Game start event loop");
    // This call blocks until the game is finished.
    game_start_event_loop();
    game_log("Game end");
    game_destroy();
    return 0;
}

void allegro5_init(void) {
    if (!al_init())
        game_abort("failed to initialize allegro");

    // Initialize add-ons.
    if (!al_init_primitives_addon())
        game_abort("failed to initialize primitives add-on");
    if (!al_init_font_addon())
        game_abort("failed to initialize font add-on");
    if (!al_init_ttf_addon())
        game_abort("failed to initialize ttf add-on");
    if (!al_init_image_addon())
        game_abort("failed to initialize image add-on");
    if (!al_install_audio())
        game_abort("failed to initialize audio add-on");
    if (!al_init_acodec_addon())
        game_abort("failed to initialize audio codec add-on");
    if (!al_reserve_samples(RESERVE_SAMPLES))
        game_abort("failed to reserve samples");
    if (!al_install_keyboard())
        game_abort("failed to install keyboard");
    if (!al_install_mouse())
        game_abort("failed to install mouse");
    // TODO: Initialize other addons such as video, ...

    // Setup game display.
    game_display = al_create_display(SCREEN_W, SCREEN_H);
    if (!game_display)
        game_abort("failed to create display");
    al_set_window_title(game_display, "I2P(I)_2020 CAT FIGHT CHIWA");

    // Setup update timer.
    game_update_timer = al_create_timer(1.0f / FPS);
    if (!game_update_timer)
        game_abort("failed to create timer");

    // Setup event queue.
    game_event_queue = al_create_event_queue();
    if (!game_event_queue)
        game_abort("failed to create event queue");

    // Malloc mouse buttons state according to button counts.
    const unsigned m_buttons = al_get_mouse_num_buttons();
    game_log("There are total %u supported mouse buttons", m_buttons);
    // mouse_state[0] will not be used.
    mouse_state = malloc((m_buttons + 1) * sizeof(bool));
    memset(mouse_state, false, (m_buttons + 1) * sizeof(bool));

    // Register display, timer, keyboard, mouse events to the event queue.
    al_register_event_source(game_event_queue, al_get_display_event_source(game_display));
    al_register_event_source(game_event_queue, al_get_timer_event_source(game_update_timer));
    al_register_event_source(game_event_queue, al_get_keyboard_event_source());
    al_register_event_source(game_event_queue, al_get_mouse_event_source());
    // TODO: Register other event sources such as timer, video, ...

    // Start the timer to update and draw the game.
    al_start_timer(game_update_timer);
}

void game_init(void) {
    /* Shared resources*/
    font_pirulen_32 = al_load_font("pirulen.ttf", 32, 0);
    if (!font_pirulen_32)
        game_abort("failed to load font: pirulen.ttf with size 32");

    font_pirulen_24 = al_load_font("pirulen.ttf", 24, 0);
    if (!font_pirulen_24)
        game_abort("failed to load font: pirulen.ttf with size 24");
    //owo score board
    font_score = al_load_font("1900805.ttf",24,0);
    if (!font_score)
        game_abort("failed to load font: 1900805.ttf with size 24");
    /* Menu Scene resources*/
    main_img_background = load_bitmap_resized("main-bg.png", SCREEN_W, SCREEN_H);

    main_bgm = al_load_sample("meow_meow.ogg");
    if (!main_bgm)
        game_abort("failed to load audio: S31-Night Prowler.ogg");
    //owo game over
    game_over_bgm = al_load_sample("game_over_music.ogg");
        if(!game_over_bgm)
            game_abort("failed to load audio: game over bgm.ogg");
    img_game_over = al_load_bitmap("game_over_scene.png");
    if (!img_game_over)
        game_abort("failed to load image: game_over.png");
    //owo winning
    winning_bgm = al_load_sample("winning.ogg");
    if(!winning_bgm)
        game_abort("failed to load audio: winning.ogg");
    img_winning = al_load_bitmap("win_background.png");
    if(!img_winning)
        game_abort("failed to load image:win_background.png");
    //owo bullet sound
    bullet_sound01 = al_load_sample("bullet_sound.ogg");
    if(!bullet_sound01)
        game_abort("failed to load audio: bullet sound.ogg");
    bullet_sound02 = al_load_sample("bullet_sound02.ogg");
    if(!bullet_sound02)
        game_abort("failed to load audio: bullet_sound02.ogg");
    //owo hidden role
    img_level_5_unlock = al_load_bitmap("level_5_unlock.png");
    img_level_10_unlock = al_load_bitmap("level_10_unlock.png");
    img_strong_cat_btm01 = al_load_bitmap("strong_cat_btm01.png");
    img_strong_cat_btm02 = al_load_bitmap("strong_cat_btm02.png");
    img_super_cat_btm01 = al_load_bitmap("super_cat_btm01.png");
    img_super_cat_btm02 = al_load_bitmap("super_cat_btm02.png");
    //owo setting board
    img_chose_char_btm = al_load_bitmap("choose_char01.png");
    img_chose_char_btm01 = al_load_bitmap("choose_char02.png");
    img_simple = al_load_bitmap("mode_buttom01.png");
    img_simple01 = al_load_bitmap("mode_buttom01_1.png");
    img_hard = al_load_bitmap("mode_buttom02.png");
    img_hard01 = al_load_bitmap("mode_buttom02_1.png");
    img_skill = al_load_bitmap("skill01.png");
    img_skill01 = al_load_bitmap("skill02.png");
    //owo click sound
    click_sound = al_load_sample("click_sound.ogg");
    if(!click_sound)
        game_abort("failed to load audio: click sound.ogg");
    //owo sound icon
    sound_icon01 = al_load_bitmap("sound_icon01.png");
    sound_icon01_1 = al_load_bitmap("sound_icon01_1.png");
    sound_icon02 = al_load_bitmap("sound_icon02.png");
    sound_icon02_1 = al_load_bitmap("sound_icon02_1.png");

    //owo select char
    setting_01 = al_load_bitmap("setting_cat01.png");
    setting_01_1 = al_load_bitmap("setting_cat01-1.png");
    setting_02 = al_load_bitmap("setting_cat02.png");
    setting_02_1 = al_load_bitmap("setting_cat02-1.png");
    select_bgm = al_load_sample("select_bgm.ogg");
    select_bg = al_load_bitmap("select_bg.png");
    if(!select_bg)
        game_abort("failed to load image:select_bg.png");
    //owo skill
    img_skill_bg = al_load_bitmap("skill_bg.png");
    skill_bgm = al_load_sample("skill_bgm.ogg");
    rule_bgm = al_load_sample("animate_bgm04.ogg");
    rule_bg = al_load_bitmap("rule_bg.png");
    //owo sound new add
    enter_sound = al_load_sample("enter.wav");
    backspace_sound = al_load_sample("backspace.wav");
    heal_sound = al_load_sample("heal.wav");
    beat_sound = al_load_sample("beat.wav");
    big_knife_sound = al_load_sample("big_knife.wav");


    // [HACKATHON 3-4]
    // TODO: Load settings images.
    // Don't forget to check their return values.
    // Uncomment and fill in the code below.
    img_settings = al_load_bitmap("settings.png");
    if (!img_settings)
        game_abort("failed to load image: settings.png");
    img_settings2 = al_load_bitmap("settings2.png");
    if (!img_settings2)
        game_abort("failed to load image: settings2.png");
    //owo restart
    img_restart01 = al_load_bitmap("restart01.png");
    img_restart02 = al_load_bitmap("restart02.png");
    //owo boss music
    boss_bgm = al_load_sample("meow_fight.ogg");


    //owo setting bg
    img_setting_bg = al_load_bitmap("setting_background.png");
    if(!img_setting_bg)
        game_abort("failed to load image: setting_bg.png");
    setting_bgm = al_load_sample("setting_bgm.ogg");
    if(!setting_bgm)
        game_abort("failed to load audio(bgm)");

    /* Start Scene resources*/
    start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);

    //owo select char
    start_img_plane = al_load_bitmap("black_cat.png");
    if (!start_img_plane)
        game_abort("failed to load image: plane.png");
    img_plane2 = al_load_bitmap("white_cat.png");
    if (!img_plane2)
        game_abort("failed to load image: plane2.png");


    start_img_enemy = al_load_bitmap("smallfighter0006.png");
    if (!start_img_enemy)
        game_abort("failed to load image: smallfighter0006.png");

    start_bgm = al_load_sample("meow_fight02.ogg");
    if (!start_bgm)
        game_abort("failed to load audio: mythica.ogg");

    // [HACKATHON 2-5]
    // TODO: Initialize bullets.
    // 1) Search for a bullet image online and put it in your project.
    //    You can use the image we provided.
    // 2) Load it in by 'al_load_bitmap' or 'load_bitmap_resized'.
    // 3) If you use 'al_load_bitmap', don't forget to check its return value.
    // Uncomment and fill in the code below.
    img_bullet =al_load_bitmap("paw.jpg");
    if (!img_bullet)
        game_abort("failed to load image: image12.png");
    //owo
    img_chiwa_attack =al_load_bitmap("chiwa_attack.png");
    if (!img_chiwa_attack)
        game_abort("failed to load image: chiwa_attack.png");
    img_angle =al_load_bitmap("angle_cat.png");
    if(!img_angle)
        game_abort("failed to load image: angle_cat.png");
    img_can =al_load_bitmap("can.png");
    if (!img_can)
        game_abort("failed to load image: can.png");
    img_boss =al_load_bitmap("boss.png");
    if (!img_boss)
        game_abort("failed to load image: boss.png");
    img_boss_sword=al_load_bitmap("boss_sword.png");
    if(!img_boss_sword)
        game_abort("failed to load image: boss_sword.png");
    img_new_bullet = al_load_bitmap("bullet02.png");
    if(!img_new_bullet)
        game_abort("failed to load image: new bullet.png");


    // Change to first scene.
    game_change_scene(SCENE_MENU);
}

void game_start_event_loop(void) {
    bool done = false;
    ALLEGRO_EVENT event;
    int redraws = 0;
    /*
    game_log("...")在運行遊戲時 有個小黑框會顯示我們的操作owo
    */
    while (!done) {
        al_wait_for_event(game_event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // Event for clicking the window close button.
            game_log("Window close button clicked");
            done = true;
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            // Event for redrawing the display.
            if (event.timer.source == game_update_timer)
                // The redraw timer has ticked.
                redraws++;
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            // Event for keyboard key down.
            game_log("Key with keycode %d down", event.keyboard.keycode);
            key_state[event.keyboard.keycode] = true;
            on_key_down(event.keyboard.keycode);
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            // Event for keyboard key up.
            game_log("Key with keycode %d up", event.keyboard.keycode);
            key_state[event.keyboard.keycode] = false;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            // Event for mouse key down.
            game_log("Mouse button %d down at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = true;
            on_mouse_down(event.mouse.button, event.mouse.x, event.mouse.y);
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Event for mouse key up.
            game_log("Mouse button %d up at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = false;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (event.mouse.dx != 0 || event.mouse.dy != 0) {
                // Event for mouse move.
                // game_log("Mouse move to (%d, %d)", event.mouse.x, event.mouse.y);
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
            } else if (event.mouse.dz != 0) {
                // Event for mouse scroll.
                game_log("Mouse scroll at (%d, %d) with delta %d", event.mouse.x, event.mouse.y, event.mouse.dz);
            }
        }
        // TODO: Process more events and call callbacks by adding more
        // entries inside Scene.

        // Redraw
        if (redraws > 0 && al_is_event_queue_empty(game_event_queue)) {
            // if (redraws > 1)
            //     game_log("%d frame(s) dropped", redraws - 1);
            // Update and draw the next frame.
            game_update();
            game_draw();
            redraws = 0;
        }
    }
}

void game_update(void) {
    if (active_scene == SCENE_START) {
        plane.vx = plane.vy = 0;
        if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W])
            plane.vy -= 1;
        if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S])
            plane.vy += 1;
        if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A])
            plane.vx -= 1;
        if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D])
            plane.vx += 1;
        // 0.71 is (1/sqrt(2)).
        //plane.y += plane.vy * 4 * (plane.vx ? 0.71f : 1);
        plane.x += plane.vx * 4 * (plane.vy ? 0.71f : 1);
        //owo select char
        new_plane.vx = new_plane.vy = 0;
        if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W])
            new_plane.vy -= 2;
        if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S])
            new_plane.vy += 2;
        if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A])
            new_plane.vx -= 2;
        if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D])
            new_plane.vx += 2;
        // 0.71 is (1/sqrt(2)).
        //new_plane.y += new_plane.vy * 4 * (new_plane.vx ? 0.71f : 1);
        new_plane.x += new_plane.vx * 4 * (new_plane.vy ? 0.71f : 1);

        //owo
        for(int i=0;i<MAX_ENEMY;i++)
            enemies[i].x += enemies[i].vx * 2 * (enemies[i].vy ? 0.71f : 1);
        // [HA
        //[HACKATHON 1-1]
        // TODO: Limit the plane's collision box inside the frame.
        //       (x, y axes can be separated.)
        // Uncomment and fill in the code below.
        if (plane.x-plane.w/2 < 0)
            plane.x = plane.w/2;
        else if (plane.x+plane.w/2 > SCREEN_W)
            plane.x = SCREEN_W-plane.w/2;
        if (plane.y-plane.h/2 < 0)
            plane.y = plane.h/2;
        else if (plane.y+plane.h/2 > SCREEN_H)
            plane.y = SCREEN_H-plane.h/2;
        //owo select char
        if (new_plane.x-new_plane.w/2 < 0)
            new_plane.x = new_plane.w/2;
        else if (new_plane.x+new_plane.w/2 > SCREEN_W)
            new_plane.x = SCREEN_W-new_plane.w/2;
        if (new_plane.y-new_plane.h/2 < 0)
            new_plane.y = new_plane.h/2;
        else if (new_plane.y+new_plane.h/2 > SCREEN_H)
            new_plane.y = SCREEN_H-new_plane.h/2;

        //owo
        for(int i=0;i<MAX_ENEMY;i++){
            if (enemies[i].x-enemies[i].w/2 < 0)
            {
                enemies[i].x = enemies[i].w/2;
                enemies[i].vx*=-1;
            }
            else if (enemies[i].x+enemies[i].w/2 > SCREEN_W)
            {
                enemies[i].x = SCREEN_W-enemies[i].w/2;
                enemies[i].vx*=-1;
            }
        }
        for(int i=0;i<MAX_ENEMY;i++)
            enemies[i].x += enemies[i].vx * 4 * (enemies[i].vy ? 0.71f : 1);

        if (angle.x-angle.w/2 < 0)
        {
            angle.x = angle.w/2;
            angle.vx*=-1;
        }
        else if (angle.x+angle.w/2 > SCREEN_W)
        {
            angle.x = SCREEN_W-angle.w/2;
            angle.vx*=-1;
        }
        angle.x += angle.vx * 2;

        // [HACKATHON 2-7]
        // TODO: Update bullet coordinates.
        // 1) For each bullets, if it's not hidden, update x, y
        // according to vx, vy.
        // 2) If the bullet is out of the screen, hide it.
        // Uncomment and fill in the code below.
        int i;
        for (i = 0; i < MAX_BULLET; i++) {
            if (bullets[i].hidden)
                continue;
            bullets[i].x += bullets[i].vx;
            bullets[i].y += bullets[i].vy* 4 * (bullets[i].vy ? 0.71f : 1);
            if ( bullets[i].y-bullets[i].h < 0 &&!(new_bullet_flag>=5))
                bullets[i].hidden = true;
        }
        //owo
        for(i=0; i< MAX_CHIWA_ATTACK;i++){
            if(chiwa_attack[i].hidden)
                continue;
            chiwa_attack[i].x += chiwa_attack[i].vx;
            chiwa_attack[i].y +=chiwa_attack[i].vy * 4 *(chiwa_attack[i].vy ? 0.71f : 1);
            if(chiwa_attack[i].y+chiwa_attack[i].h > SCREEN_H )
                chiwa_attack[i].hidden = true;
        }
        for(i=0; i< MAX_BOSS_SWORD;i++){
            if(boss_sword[i].hidden)
                continue;
            boss_sword[i].x += boss_sword[i].vx;
            boss_sword[i].y +=boss_sword[i].vy ;
            if(boss_sword[i].y+boss_sword[i].h/2 > SCREEN_H )
                boss_sword[i].hidden = true;
        }
        //owo 新子彈
        for(i=0; i< MAX_NEW_BULLET;i++){
            if(new_bullet[i].hidden)
                continue;
            new_bullet[i].x += new_bullet[i].vx;
            new_bullet[i].y +=new_bullet[i].vy ;
            if(new_bullet[i].y-new_bullet[i].h/2 < 0 &&new_bullet_flag>=5)
                new_bullet[i].hidden = true;
        }
        //owo補師
        for(i=0; i< MAX_CAN;i++){
            if(can[i].hidden)
                continue;
            can[i].x+=can[i].vx;
            can[i].y+=can[i].vy*2;
            if(can[i].y+can[i].h >SCREEN_H)
                can[i].hidden = true;
            if (can[i].x-can[i].w/2 < 0)
            {
                can[i].x = can[i].w/2;
                can[i].vx*=-1;
            }
            else if (can[i].x+can[i].w/2 > SCREEN_W)
            {
                can[i].x = SCREEN_W-can[i].w/2;
                can[i].vx*=-1;
            }
        }

        //owo 刀打到貓
        for(i=0; i< MAX_CHIWA_ATTACK;i++)
        {
            if(select_char==1){
                if(pnt_in_rect(chiwa_attack[i].x,chiwa_attack[i].y,plane.x,plane.y,plane.w/2,plane.h/2)&&!chiwa_attack[i].hidden)
                {
                    plane.blood-=chiwa_attack[i].blood;
                    chiwa_attack[i].hidden = true;
                    score-=5;
                }
            }
            //owo select char
            else if(select_char==2){
                if(pnt_in_rect(chiwa_attack[i].x,chiwa_attack[i].y,new_plane.x,new_plane.y,new_plane.w/2,new_plane.h/2)&&!chiwa_attack[i].hidden)
                {
                    new_plane.blood-=chiwa_attack[i].blood;
                    chiwa_attack[i].hidden = true;
                    score-=10;
                }
            }
        }
        //owo貓爪抓到吉娃
        for(int j=0;j<MAX_ENEMY;j++)
        {
            for(i=0;i<MAX_BULLET;i++)
            {
                if(pnt_in_rect(bullets[i].x,bullets[i].y,enemies[j].x,enemies[j].y+bullets[i].h/2,enemies[j].w/2,enemies[j].h/2)&&!bullets[i].hidden&&!enemies[j].hidden)
                {
                    //if(all_sound) al_play_sample(beat_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&beat_sound_id);
                    enemies[j].blood -= bullets[i].blood;
                    if(!enemies[j].hidden&&select_char==1)score++;
                    if(!enemies[j].hidden&&select_char==2)score+=5;
                    bullets[i].hidden = true;

                }
            }

        }
        //owo貓貓用力打吉娃
        for(int j=0;j<MAX_ENEMY;j++)
        {
            for(i=0;i<MAX_NEW_BULLET;i++)
            {
                if(pnt_in_rect(new_bullet[i].x,new_bullet[i].y,enemies[j].x,enemies[j].y+new_bullet[i].h/2,enemies[j].w/2,enemies[j].h)&&!new_bullet[i].hidden&&!enemies[j].hidden)
                {
                    //if(all_sound) al_play_sample(beat_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&beat_sound_id);
                    enemies[j].blood -= new_bullet[i].blood;
                    new_bullet[i].hidden = true;
                    if(!enemies[j].hidden&&select_char==1)score+=3;
                    if(!enemies[j].hidden&&select_char==2)score+=10;
                }
            }
        }
        //owo貓貓打boss
        if(!boss.hidden)
        {
            for(i=0;i<MAX_BULLET;i++)
            {
                if(pnt_in_rect(bullets[i].x,bullets[i].y,boss.x,boss.y,boss.w/4,boss.h)&&!bullets[i].hidden)
                {
                    //if(all_sound) al_play_sample(beat_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&beat_sound_id);
                    boss.blood-=bullets[i].blood;
                    bullets[i].hidden = true;
                    if(!boss.hidden&&select_char==1)score+=3;
                    if(!boss.hidden&&select_char==2)score+=10;
                }
            }
        }
        //owo貓貓用力打boss
        if(!boss.hidden)
        {
            for(i=0;i<MAX_NEW_BULLET;i++)
            {
                if(pnt_in_rect(new_bullet[i].x,new_bullet[i].y,boss.x,boss.y,boss.w/4,boss.h)&&!new_bullet[i].hidden)
                {
                    //if(all_sound) al_play_sample(beat_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&beat_sound_id);
                    boss.blood-=new_bullet[i].blood;
                    new_bullet[i].hidden = true;
                    if(!boss.hidden&&select_char==1)score+=5;
                    if(!boss.hidden&&select_char==2)score+=15;
                }
            }
        }
        //owo貓被boss打
        for(i=0; i< MAX_BOSS_SWORD;i++)
        {
            //owo select char
            if(select_char==1){
                if(pnt_in_rect(boss_sword[i].x,boss_sword[i].y+boss_sword[i].h/2,plane.x,plane.y,plane.w/2,plane.h/2)&&!boss_sword[i].hidden)
                {
                    if(all_sound)al_play_sample(big_knife_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&big_knife_sound_id);
                    plane.blood-=boss_sword[i].blood;
                    boss_sword[i].hidden = true;
                    score-=20;
                }
            }
            else if(select_char==2){
                if(pnt_in_rect(boss_sword[i].x,boss_sword[i].y+boss_sword[i].h/2,new_plane.x,new_plane.y,new_plane.w/2,new_plane.h/2)&&!boss_sword[i].hidden)
                {
                    if(all_sound)al_play_sample(big_knife_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&big_knife_sound_id);
                    new_plane.blood-=boss_sword[i].blood;
                    boss_sword[i].hidden = true;
                    score-=30;
                }
            }
        }

        //owo貓貓吃罐罐
        for(i=0; i< MAX_CAN;i++)
        {
            //owo select char
            if(select_char==1){
                if(pnt_in_rect(can[i].x,can[i].y,plane.x,plane.y,plane.w/2,plane.h/2)&&!can[i].hidden)
                {
                    if(all_sound) al_play_sample(heal_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&heal_sound_id);
                    plane.blood+=can[i].blood;
                    can[i].hidden = true;
                    new_bullet_flag++;
                    score+=2;
                }
            }
            else if(select_char==2){
                if(pnt_in_rect(can[i].x,can[i].y,new_plane.x,new_plane.y,new_plane.w/2,new_plane.h/2)&&!can[i].hidden)
                {
                    if(all_sound) al_play_sample(heal_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&heal_sound_id);
                    new_plane.blood+=can[i].blood;
                    can[i].hidden = true;
                    new_bullet_flag++;
                    score+=2;
                }
            }
        }

        int bossflag=0;
        //owo吉娃掛了
        for(i=0;i<MAX_ENEMY;i++)
            if(enemies[i].blood<=0)
               {
                   enemies[i].hidden = true;
                   bossflag++;
               }

        if(bossflag==MAX_ENEMY)
         {
             boss.hidden = false;
             angle.hidden = true;


             if(little_flag)
             {
                 al_stop_sample(&start_bgm_id);
                 if(all_sound) al_play_sample(boss_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&boss_bgm_id);
                 start_img_background = al_load_bitmap("boss_bg.png");
                 bossbgmflag = 0;
             }
             little_flag=0;
         }

        //owo貓貓掛了QAQ
        if(plane.blood<=0)
            plane.hidden = true;
        if(new_plane.blood<=0)
            new_plane.hidden = true;

        //owo boss掛了
        if(boss.blood<=0)
            boss.hidden = true;

        // [HACKATHON 2-8]
        // TODO: Shoot if key is down and cool-down is over.
        // 1) Get the time now using 'al_get_time'.
        // 2) If Space key is down in 'key_state' and the time
        //    between now and last shoot is not less that cool
        //    down time.
        // 3) Loop through the bullet array and find one that is hidden.
        //    (This part can be optimized.)
        // 4) The bullet will be found if your array is large enough.
        // 5) Set the last shoot time to now.
        // 6) Set hidden to false (recycle the bullet) and set its x, y to the
        //    front part of your plane.
        // Uncomment and fill in the code below.
        double now = al_get_time();
        if (key_state[ALLEGRO_KEY_SPACE] && now - last_shoot_timestamp >= MAX_COOLDOWN ) {
            for (i = 0; i < MAX_BULLET; i++) {
                if (bullets[i].hidden && !(plane.hidden&&new_plane.hidden)) {
                    last_shoot_timestamp = now;
                    bullets[i].hidden = false;
                    //owo select char
                    if(select_char==1){
                        bullets[i].x = plane.x;
                        bullets[i].y = plane.y-plane.h/2;
                        if(bullet_sound&&all_sound) al_play_sample(bullet_sound01,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&bullet_sound01_id);
                    }
                    else if(select_char==2) {
                        bullets[i].x =new_plane.x;
                        bullets[i].y = new_plane.y-new_plane.h/2;
                        if(bullet_sound&&all_sound) al_play_sample(bullet_sound01,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&bullet_sound01_id);
                    }

                    break;
                }
            }
        }
        //owo
        if(now-chiwa_last_shoot_timestamp >= MAX_CHIWA_COOLDOWN){
            for(int j=0;j<MAX_ENEMY;j++){
                for(i=0; i < MAX_CHIWA_ATTACK;i++){
                    if (chiwa_attack[i].hidden && !enemies[j].hidden){
                        chiwa_last_shoot_timestamp = now;
                        chiwa_attack[i].hidden = false;
                        chiwa_attack[i].x = enemies[j].x;
                        chiwa_attack[i].y = enemies[j].y+enemies[j].h/2;
                        break;
                    }
                }
            }
        }
        if(now-can_last_shoot_timestamp >= MAX_CAN_COOLDOWN){
            for(i=0; i < MAX_CAN;i++){
                if (can[i].hidden&&!angle.hidden){
                    can_last_shoot_timestamp = now;
                    can[i].hidden = false;
                    can[i].x = angle.x;
                    can[i].y = angle.y+angle.h/2;
                    break;
                }
            }

        }
        if(now-boss_sword_last_shoot_timestamp >= MAX_BOSS_SWORD_COOLDOWN){
            for(i=0; i < MAX_BOSS_SWORD;i++){
                if (boss_sword[i].hidden&&!boss.hidden){
                    boss_sword_last_shoot_timestamp = now;
                    boss_sword[i].hidden = false;
                    boss_sword[i].x = boss.x;
                    boss_sword[i].y = boss.y+boss.h/2;
                    break;
                }
            }

        }
        if(key_state[ALLEGRO_KEY_SPACE] && now-new_bullet_last_shoot_timestamp >= MAX_NEW_BULLET_COOLDOWN){
            for(i=0; i < MAX_NEW_BULLET;i++){
                if (new_bullet[i].hidden&&!(plane.hidden&&new_plane.hidden)){
                    new_bullet_last_shoot_timestamp = now;
                    new_bullet[i].hidden = false;
                    //owo select char
                    if(select_char==1){
                        new_bullet[i].x = plane.x;
                        new_bullet[i].y = plane.y-plane.h/2;
                        if(bullet_sound&&all_sound) al_play_sample(bullet_sound02,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&bullet_sound02_id);
                    }
                    else if(select_char==2) {
                        new_bullet[i].x =new_plane.x;
                        new_bullet[i].y = new_plane.y-new_plane.h/2;
                        if(bullet_sound&&all_sound) al_play_sample(bullet_sound02,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&bullet_sound02_id);
                    }
                    break;
                }
            }

        }




    }
}

void game_draw(void) {
    if (active_scene == SCENE_MENU) {
        al_draw_bitmap(main_img_background, 0, 0, 0);
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W / 2, 225, ALLEGRO_ALIGN_CENTER, "!!Cat Fight ChiWa!!");
        al_draw_text(font_pirulen_24, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H -100,ALLEGRO_ALIGN_CENTER, " Press enter to start");
        al_draw_text(font_pirulen_24, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H - 50,ALLEGRO_ALIGN_CENTER, " Press A to animation");
        // [HACKATHON 3-5]
        // TODO: Draw settings images.
        // The settings icon should be located at (x, y, w, h) =
        // (SCREEN_W - 48, 10, 38, 38).
        // Change its image according to your mouse position.
        // Uncomment and fill in the code below.
        if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W-48, 10, 38, 38))
            al_draw_bitmap(img_settings2, SCREEN_W-48,10, 0);
        else
            al_draw_bitmap(img_settings, SCREEN_W-48, 10, 0);
        if(all_sound){
            if(pnt_in_rect(mouse_x, mouse_y, SCREEN_W-48, 90, 38, 38))
                al_draw_bitmap(sound_icon01_1,SCREEN_W-48, 90,0);
            else
                al_draw_bitmap(sound_icon01,SCREEN_W-48,90,0);
        }
        else{
            if(pnt_in_rect(mouse_x, mouse_y, SCREEN_W-48, 90, 38, 38))
                al_draw_bitmap(sound_icon01,SCREEN_W-48, 90,0);
            else
                al_draw_bitmap(sound_icon01_1,SCREEN_W-48,90,0);
        }
        if(bullet_sound){
            if(pnt_in_rect(mouse_x, mouse_y, 28, 10, 38, 38))
                al_draw_bitmap(sound_icon02_1,28, 10,0);
            else
                al_draw_bitmap(sound_icon02,28,10,0);
        }
        else{
            if(pnt_in_rect(mouse_x, mouse_y, 28, 10, 38, 38))
                al_draw_bitmap(sound_icon02,28, 10,0);
            else
                al_draw_bitmap(sound_icon02_1,28,10,0);
        }

    } else if (active_scene == SCENE_START) {
        int i;
        al_draw_bitmap(start_img_background, 0, 0, 0);
        //owo score boarde
        sprintf(score_text,"%d",score);
        //owo select char
        if(select_char==1) sprintf(hp_text,"%d",plane.blood);
        else if(select_char==2) sprintf(hp_text,"%d",new_plane.blood);
        sprintf(cans_text,"%d",new_bullet_flag);
        al_draw_text(font_score, al_map_rgb(255,255,255),SCREEN_W-200,50,ALLEGRO_ALIGN_LEFT,"Score: ");
        al_draw_text(font_score, al_map_rgb(255,255,255),SCREEN_W-100,50,ALLEGRO_ALIGN_LEFT,score_text);

        al_draw_text(font_score, al_map_rgb(255,255,255),SCREEN_W-200,100,ALLEGRO_ALIGN_LEFT,"Hp: ");
        al_draw_text(font_score, al_map_rgb(255,255,255),SCREEN_W-100,100,ALLEGRO_ALIGN_LEFT,hp_text);

        al_draw_text(font_score, al_map_rgb(255,255,255),SCREEN_W-200,150,ALLEGRO_ALIGN_LEFT,"Cans: ");
        al_draw_text(font_score, al_map_rgb(255,255,255),SCREEN_W-100,150,ALLEGRO_ALIGN_LEFT,cans_text);

        // [HACKATHON 2-9]
        // TODO: Draw all bullets in your bullet array.
        // Uncomment and fill in the code below.
        for (int i=0;i<MAX_BULLET;i++)
            draw_movable_object(bullets[i]);
        //owo
        for(int i=0;i<MAX_CHIWA_ATTACK;i++)
            draw_movable_object(chiwa_attack[i]);
        draw_movable_object(plane);
        //owo select char
        draw_movable_object(new_plane);
        for (i = 0; i < MAX_ENEMY; i++)
            draw_movable_object(enemies[i]);
        draw_movable_object(angle);
        for(i=0;i< MAX_CAN;i++)
            draw_movable_object(can[i]);
        if(!boss.hidden){
            for(i=0;i< MAX_BOSS_SWORD;i++)
                draw_movable_object(boss_sword[i]);
        }
        if(new_bullet_flag>=5)
            for(i=0;i<MAX_NEW_BULLET;i++)
                draw_movable_object(new_bullet[i]);

        //owo可否畫長方形
        ALLEGRO_COLOR green = al_map_rgb(0,255,0);
        ALLEGRO_COLOR red = al_map_rgb(255,0,0);
        ALLEGRO_COLOR orange = al_map_rgb(255,97,3);
        //owo select char
        if(select_char==1){
            if(plane.blood>0)
                al_draw_filled_rectangle(plane.x-plane.blood, plane.y-plane.h/2+3 , plane.x+plane.blood , plane.y-plane.h/2 ,green );
        }
        else if(select_char==2){
            if(new_plane.blood>0)
                al_draw_filled_rectangle(new_plane.x-new_plane.blood, new_plane.y-new_plane.h/2+3 , new_plane.x+new_plane.blood , new_plane.y-new_plane.h/2 ,green );
        }
        for(int i=0;i<MAX_ENEMY;i++)
        {
            if(enemies[i].blood>0)
                al_draw_filled_rectangle(enemies[i].x-enemies[i].blood,enemies[i].y-enemies[i].h/2+3,enemies[i].x+enemies[i].blood,enemies[i].y-enemies[i].h/2,orange);

        }
        draw_movable_object(boss);
        if(!boss.hidden && boss.blood>0)
        {
            al_draw_filled_rectangle(boss.x-boss.blood,boss.y-boss.h/2+3,boss.x+boss.blood,boss.y-boss.h/2,red);
        }
        //owo game over
        if(plane.hidden&&new_plane.hidden)
        {
            al_rest(3);
            win_time++;
            game_change_scene(SCENE_GEME_OVER);
        }

        if(boss.hidden&&angle.hidden)
        {
            al_rest(3);
            if(score>0) win_time+=5;
            game_change_scene(SCENE_WIN);
        }



    }
    // [HACKATHON 3-9]
    // TODO: If active_scene is SCENE_SETTINGS.
    // Draw anything you want, or simply clear the display.
    else if (active_scene == SCENE_SETTINGS) {
        al_draw_bitmap(img_setting_bg,0,0,0);

        //owo setting board
        al_draw_text(font_score,al_map_rgb(0,0,0),478,156,ALLEGRO_ALIGN_CENTER,"Choose your cat:");
        if(pnt_in_rect(mouse_x-20, mouse_y-30, 358,206, 248,74))
            al_draw_bitmap(img_chose_char_btm01,358,206,0);
        else
            al_draw_bitmap(img_chose_char_btm,358,206,0);
        al_draw_text(font_score,al_map_rgb(0,0,0),478,306,ALLEGRO_ALIGN_CENTER,"Choose Hardness:");
        if(pnt_in_rect(mouse_x-20, mouse_y-30, 289,350, 125,89))
            al_draw_bitmap(img_simple01,289,350,0);
        else
            al_draw_bitmap(img_simple,289,350,0);

        if(pnt_in_rect(mouse_x-20, mouse_y-30, 530,350, 125,89))
            al_draw_bitmap(img_hard01,530,350,0);
        else
            al_draw_bitmap(img_hard,530,350,0);
        al_draw_text(font_score,al_map_rgb(0,0,0),478,456,ALLEGRO_ALIGN_CENTER,"Little Skill:");
        if(pnt_in_rect(mouse_x-20, mouse_y-30, 420,500, 104,51))
            al_draw_bitmap(img_skill01,420,500,0);
        else
            al_draw_bitmap(img_skill,420,500,0);

    }
    //owo game over
    else if(active_scene == SCENE_GEME_OVER){
        al_draw_bitmap(img_game_over,0,0,0);
        //owo restart
        if (pnt_in_rect(mouse_x-20, mouse_y-30, 420,400, 99, 30))
            al_draw_bitmap(img_restart02,440,400,0);
        else
        al_draw_bitmap(img_restart01,440,400,0);

        al_draw_text(font_score, al_map_rgb(255,255,255),420,350,ALLEGRO_ALIGN_LEFT,"Score: ");
        al_draw_text(font_score, al_map_rgb(255,255,255),520,350,ALLEGRO_ALIGN_LEFT,score_text);
        sprintf(win_time_text,"%d",win_time);
        al_draw_text(font_score, al_map_rgb(255,255,255),430,230,ALLEGRO_ALIGN_LEFT,"Level: ");
        al_draw_text(font_score, al_map_rgb(255,255,255),530,230,ALLEGRO_ALIGN_LEFT,win_time_text);
    }
    //owo winning
    else if(active_scene == SCENE_WIN){
        al_draw_bitmap(img_winning,0,0,0);
        //owo restart
        if (pnt_in_rect(mouse_x-20, mouse_y-30, 460,450, 99, 30))
            al_draw_bitmap(img_restart02,450,470,0);
        else
        al_draw_bitmap(img_restart01,450,470,0);

        al_draw_text(font_score, al_map_rgb(0,0,0),430,350,ALLEGRO_ALIGN_LEFT,"Score: ");
        al_draw_text(font_score, al_map_rgb(0,0,0),530,350,ALLEGRO_ALIGN_LEFT,score_text);
        sprintf(win_time_text,"%d",win_time);
        al_draw_text(font_score, al_map_rgb(0,0,0),430,300,ALLEGRO_ALIGN_LEFT,"Level: ");
        al_draw_text(font_score, al_map_rgb(0,0,0),530,300,ALLEGRO_ALIGN_LEFT,win_time_text);
     }
    //owo select char
    else if(active_scene == SCENE_SELECT){
        al_draw_bitmap(select_bg, 0, 0, 0);
        if (pnt_in_rect(mouse_x-20, mouse_y-30, 264,329, 90, 48))
        {
            al_draw_bitmap(setting_01_1, 264,329, 0);
        }
        else
            al_draw_bitmap(setting_01, 264,329, 0);
        if (pnt_in_rect(mouse_x-20, mouse_y-30, 639,329, 90, 48))
        {
            al_draw_bitmap(setting_02_1, 639,329, 0);
        }
        else
            al_draw_bitmap(setting_02, 639,329, 0);
        //owo hidden role
        if(win_time<5) al_draw_bitmap(img_level_5_unlock,264,429,0);
        if(win_time<10) al_draw_bitmap(img_level_10_unlock,639,429,0);
        if(win_time>=5){
            if(pnt_in_rect(mouse_x-20, mouse_y-30, 264,429, 90, 48))
            {
                al_draw_bitmap(img_strong_cat_btm02,264,429,0);
            }
            else
                al_draw_bitmap(img_strong_cat_btm01,264,429,0);
        }
        if(win_time>=10){
            if(pnt_in_rect(mouse_x-20, mouse_y-30, 639,429, 90, 48))
            {
                al_draw_bitmap(img_super_cat_btm02,639,429,0);
            }
            else
                al_draw_bitmap(img_super_cat_btm01,639,429,0);
        }
        sprintf(win_time_text,"%d",win_time);
        al_draw_text(font_score, al_map_rgb(255,255,255),430,200,ALLEGRO_ALIGN_LEFT,"Level: ");
        al_draw_text(font_score, al_map_rgb(255,255,255),530,200,ALLEGRO_ALIGN_LEFT,win_time_text);

    }
    //owo skill
    else if(active_scene == SCENE_SKILL){
        al_draw_bitmap(img_skill_bg,0,0,0);
    }
    else if(active_scene == SCENE_RULE){
        al_draw_bitmap(rule_bg,0,0,0);
    }
    //owo animate
    else if(active_scene == SCENE_ANIMATE){
        for(int i=1;i<14;i++)
        {
            ALLEGRO_SAMPLE *bgm01;
            ALLEGRO_SAMPLE_ID bgm01_id;
            ALLEGRO_SAMPLE *bgm02;
            ALLEGRO_SAMPLE_ID bgm02_id;
            ALLEGRO_SAMPLE *bgm03;
            ALLEGRO_SAMPLE_ID bgm03_id;
            ALLEGRO_SAMPLE *bgm04;
            ALLEGRO_SAMPLE_ID bgm04_id;
            if(i==1){

                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate01.png");
                    bgm01 = al_load_sample("animate_bgm01.ogg");
                    al_draw_bitmap(img,0,0,0);
                    if(all_sound) al_play_sample(bgm01,2,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&bgm01_id);
                    al_flip_display();
                    al_rest(5);
                    al_destroy_bitmap(img);
            }
            else if(i==2){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate02.png");
                    //bgm = al_load_sample();
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(5);
                    al_destroy_bitmap(img);
            }
            else if(i==3){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate03.png");
                    //bgm = al_load_sample();
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(5);
                    al_destroy_bitmap(img);
            }
            else if(i==4){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate04.png");
                    bgm02 = al_load_sample("animate_bgm02.ogg");
                    if(all_sound) al_play_sample(bgm02,2,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&bgm02_id);
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(5);
                    al_destroy_bitmap(img);
            }
            else if(i==5){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate05.png");
                    al_destroy_sample(bgm02);
                    bgm03 = al_load_sample("animate_bgm03.ogg");
                    if(all_sound) al_play_sample(bgm03,4,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&bgm03_id);
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(5);
                    al_destroy_bitmap(img);
                    //al_destroy_sample();
            }
            else if(i==6){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate06.png");
                    //bgm = al_load_sample();
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(5);
                    al_destroy_bitmap(img);
                    //al_destroy_sample();
            }
            else if(i==7){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate07.png");
                    //bgm = al_load_sample();
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(3);
                    al_destroy_bitmap(img);
                    //al_destroy_sample();
            }
            else if(i==8){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate08.png");
                    //bgm = al_load_sample();
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(3);
                    al_destroy_bitmap(img);
                    //al_destroy_sample();
            }
            else if(i==9){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate09.png");
                    //bgm = al_load_sample();
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(3);
                    al_destroy_bitmap(img);
                    //al_destroy_sample();
            }
            else if(i==10){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate10.png");
                    //bgm = al_load_sample();
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(5);
                    al_destroy_bitmap(img);
                    //al_destroy_sample();
            }
            else if(i==11){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate11.png");
                    //bgm = al_load_sample();
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(5);
                    al_destroy_bitmap(img);
                    //al_destroy_sample();
            }
            else if(i==12){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate12.png");
                    //bgm = al_load_sample();
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(5);
                    al_destroy_bitmap(img);
                    al_destroy_sample(bgm01);
            }
            else if(i==13){
                    ALLEGRO_BITMAP *img;
                    img = al_load_bitmap("animate13.png");
                    al_destroy_sample(bgm03);
                    bgm04 = al_load_sample("animate_bgm04.ogg");
                    if(all_sound) al_play_sample(bgm04,2,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&bgm04_id);
                    al_draw_bitmap(img,0,0,0);
                    al_flip_display();
                    al_rest(15);
                    al_destroy_bitmap(img);
                    al_destroy_sample(bgm04);
                    if(select_char==1) plane.blood=100,plane.hidden=false;
                    else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
                    boss.blood = 500;
                    for(int i=0;i<MAX_ENEMY;i++)
                    enemies[i].blood=enemyblood,enemies[i].hidden=false;
                    score =0 ;
                    new_bullet_flag = 0;
                    angle.hidden = false;
                    little_flag = 1;
                    game_change_scene(SCENE_START);
                }

            }
    }
    al_flip_display();
}

void game_destroy(void) {
    // Destroy everything you have created.
    // Free the memories allocated by malloc or allegro functions.
    // Destroy shared resources.
    al_destroy_font(font_pirulen_32);
    al_destroy_font(font_pirulen_24);

    /* Menu Scene resources*/
    al_destroy_bitmap(main_img_background);
    al_destroy_sample(main_bgm);
    // [HACKATHON 3-6]
    // TODO: Destroy the 2 settings images.
    // Uncomment and fill in the code below.
    al_destroy_bitmap(img_settings);
    al_destroy_bitmap(img_settings2);

    /* Start Scene resources*/
    al_destroy_bitmap(start_img_background);
    al_destroy_bitmap(start_img_plane);
    //owo select char
    al_destroy_bitmap(img_plane2);
    al_destroy_bitmap(start_img_enemy);
    al_destroy_sample(start_bgm);
    //owo skill
    al_destroy_bitmap(img_skill_bg);
    al_destroy_sample(skill_bgm);
    al_destroy_sample(rule_bgm);
    al_destroy_bitmap(rule_bg);
    // [HACKATHON 2-10]
    // TODO: Destroy your bullet image.
    // Uncomment and fill in the code below.
    al_destroy_bitmap(img_bullet);
    //owo
    al_destroy_bitmap(img_chiwa_attack);
    al_destroy_bitmap(img_angle);
    al_destroy_bitmap(img_can);
    al_destroy_bitmap(img_boss);
    al_destroy_bitmap(img_boss_sword);
    //owo hidden role
    al_destroy_bitmap(img_level_5_unlock);
    al_destroy_bitmap(img_level_10_unlock);
    al_destroy_bitmap(img_strong_cat_btm01);
    al_destroy_bitmap(img_strong_cat_btm02);
    al_destroy_bitmap(img_super_cat_btm01);
    al_destroy_bitmap(img_super_cat_btm02);
    //owo setting
    al_destroy_sample(setting_bgm);
    al_destroy_bitmap(img_setting_bg);
    //owo game over
    al_destroy_bitmap(img_game_over);
    al_destroy_sample(game_over_bgm);
    //owo winning
    al_destroy_bitmap(img_winning);
    al_destroy_sample(winning_bgm);
    al_destroy_bitmap(img_new_bullet);
    //owo select char
    al_destroy_bitmap(setting_01);
    al_destroy_bitmap(setting_01_1);
    al_destroy_bitmap(setting_02);
    al_destroy_bitmap(setting_02_1);
    al_destroy_bitmap(select_bg);
    al_destroy_sample(select_bgm);
    //owo sound icon
    al_destroy_bitmap(sound_icon01);
    al_destroy_bitmap(sound_icon01_1);
    al_destroy_bitmap(sound_icon02);
    al_destroy_bitmap(sound_icon02_1);
    //owo bullet sound
    al_destroy_sample(bullet_sound01);
    al_destroy_sample(bullet_sound02);
    //owo restart
    al_destroy_bitmap(img_restart01);
    al_destroy_bitmap(img_restart02);
    //owo setting board
    al_destroy_bitmap(img_chose_char_btm);
    al_destroy_bitmap(img_chose_char_btm01);
    al_destroy_bitmap(img_simple);
    al_destroy_bitmap(img_simple01);
    al_destroy_bitmap(img_hard);
    al_destroy_bitmap(img_hard01);
    al_destroy_bitmap(img_skill);
    al_destroy_bitmap(img_skill01);
    //owo boss music
    al_destroy_sample(boss_bgm);
    //owo sound new add
    al_destroy_sample(enter_sound);
    al_destroy_sample(backspace_sound);
    al_destroy_sample(heal_sound);
    al_destroy_sample(beat_sound);
    al_destroy_sample(big_knife_sound);



    al_destroy_timer(game_update_timer);
    al_destroy_event_queue(game_event_queue);
    al_destroy_display(game_display);
    free(mouse_state);
}

void game_change_scene(int next_scene) {
    game_log("Change scene from %d to %d", active_scene, next_scene);
    // TODO: Destroy resources initialized when creating scene.
    if (active_scene == SCENE_MENU) {
        al_stop_sample(&main_bgm_id);
        game_log("stop audio (bgm)");
    } else if (active_scene == SCENE_START) {
        al_stop_sample(&start_bgm_id);
        game_log("stop audio (bgm)");
        al_stop_sample(&boss_bgm_id);
        game_log("stop audio (bgm)");
    }//owo game over
    else if(active_scene == SCENE_GEME_OVER){
        al_stop_sample(&game_over_bgm_id);
        game_log("stop audio(bgm)");
    }//owo winning
    else if(active_scene == SCENE_WIN){
        al_stop_sample(&winning_bgm_id);
        game_log("stop audio(bgm)");
    }//owo setting
    else if(active_scene == SCENE_SETTINGS){
        al_stop_sample(&setting_bgm_id);
        game_log("stop audio(bgm)");
    }
    //owo select char
    else if(active_scene == SCENE_SELECT){
        al_stop_sample(&select_bgm_id);
        game_log("stop audio(bgm)");
    }
    //owo skill
    else if(active_scene == SCENE_SKILL){
        al_stop_sample(&skill_bgm_id);
    }
    else if(active_scene == SCENE_RULE){
        al_stop_sample(&rule_bgm_id);
    }
    active_scene = next_scene;
    // TODO: Allocate resources before entering scene.
    if (active_scene == SCENE_MENU) {
        if(all_sound) al_play_sample(main_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &main_bgm_id);

    } else if (active_scene == SCENE_START) {
        int i;
        plane.img = start_img_plane;
        plane.x = 400;
        plane.y = 500;
        plane.w = al_get_bitmap_width(plane.img);
        plane.h = al_get_bitmap_height(plane.img);
        //owo
        plane.blood = 100;
        if(select_char==2) plane.hidden = true;
        //owo select char
        new_plane.img = img_plane2;
        new_plane.x = 400;
        new_plane.y = 500;
        new_plane.w = al_get_bitmap_width(img_plane2);
        new_plane.h = al_get_bitmap_height(img_plane2);
        //owo
        new_plane.blood = 200;
        if(select_char==1) new_plane.hidden = true;

        for (i = 0; i < MAX_ENEMY; i++) {
            enemies[i].img = start_img_enemy;
            enemies[i].w = al_get_bitmap_width(start_img_enemy);
            enemies[i].h = al_get_bitmap_height(start_img_enemy);
            enemies[i].x = enemies[i].w / 2 + (float)rand() / RAND_MAX * (SCREEN_W - enemies[i].w);
            enemies[i].y = 80;
            //owo
            enemies[i].vx = 1;
            enemies[i].blood = enemyblood;

        }
        // owo補師上線
        angle.img = img_angle;
        angle.x = angle.w / 2 + (float)rand() / RAND_MAX * (SCREEN_W - angle.w);
        angle.y = 50;
        angle.w = al_get_bitmap_width(img_angle);
        angle.h = al_get_bitmap_height(img_angle);
        angle.vx = 1;

        // [HACKATHON 2-6]
        // TODO: Initialize bullets.
        // For each bullets in array, set their w and h to the size of
        // the image, and set their img to bullet image, hidden to true,
        // (vx, vy) to (0, -3).
        // Uncomment and fill in the code below.
        for (i = 0; i < MAX_BULLET; i++) {
            bullets[i].w = al_get_bitmap_width(img_bullet);
            bullets[i].h = al_get_bitmap_height(img_bullet);
            bullets[i].img = img_bullet;
            bullets[i].vx = 0;
            bullets[i].vy = -3;
            bullets[i].hidden = true;
            //owo
            bullets[i].blood = 5;
        }
        //owo
        for(int i=0;i<MAX_CHIWA_ATTACK;i++){
            chiwa_attack[i].w=al_get_bitmap_width(img_chiwa_attack);
            chiwa_attack[i].h=al_get_bitmap_height(img_chiwa_attack);
            chiwa_attack[i].img = img_chiwa_attack;
            chiwa_attack[i].vx=0+(float)rand() / RAND_MAX * 5;
            chiwa_attack[i].vy=2;
            chiwa_attack[i].hidden = true;
            chiwa_attack[i].blood = chiattackblood;

        }
        for(int i=0;i<MAX_CAN;i++){
            can[i].w=al_get_bitmap_width(img_can);
            can[i].h=al_get_bitmap_height(img_can);
            can[i].img = img_can;
            can[i].vx=canvx;
            can[i].vy=1;
            can[i].hidden = true;
            can[i].blood = 5;
        }
        boss.w=al_get_bitmap_width(img_boss);
        boss.h=al_get_bitmap_height(img_boss);
        boss.img=img_boss;
        boss.x=SCREEN_W/2;
        boss.y=80;
        boss.vx=0;
        boss.vy=0;
        boss.hidden = true;
        boss.blood = 500;
        for(int i=0;i<MAX_BOSS_SWORD_COOLDOWN;i++){
            boss_sword[i].w=al_get_bitmap_width(img_boss_sword);
            boss_sword[i].h=al_get_bitmap_height(img_boss_sword);
            boss_sword[i].img = img_boss_sword;
            boss_sword[i].vx=0;
            boss_sword[i].vy=bossswordvy;
            boss_sword[i].hidden = true;
            boss_sword[i].blood = 50;

        }
        for (i = 0; i < MAX_NEW_BULLET; i++) {
            new_bullet[i].w = al_get_bitmap_width(img_new_bullet);
            new_bullet[i].h = al_get_bitmap_height(img_new_bullet);
            new_bullet[i].img = img_new_bullet;
            new_bullet[i].vx = 0;
            new_bullet[i].vy = -5;
            new_bullet[i].hidden = true;
            new_bullet[i].blood = 10;
        }
        if(all_sound){
            if (!al_play_sample(start_bgm, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &start_bgm_id))
                game_abort("failed to play audio (bgm)");
        }
    }
    //owo game over
    else if(active_scene == SCENE_GEME_OVER)
    {
        if(all_sound){
            if (!al_play_sample(game_over_bgm, 3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &game_over_bgm_id))
                game_abort("failed to play audio (bgm)");
        }
    }
    //owo winning
    else if(active_scene == SCENE_WIN)
    {
        if(all_sound){
            if(!al_play_sample(winning_bgm, 3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &winning_bgm_id))
                game_abort("failed to play audio (bgm)");
        }
    }
    //owo setting
    else if(active_scene == SCENE_SETTINGS)
    {
        if(all_sound){
            if(!al_play_sample(setting_bgm, 2, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &setting_bgm_id))
                game_abort("failed to play audio(bgm)");
        }
    }
    else if(active_scene == SCENE_SELECT)
    {
        if(all_sound){
            if (!al_play_sample(select_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &select_bgm_id))
                game_abort("failed to play audio (bgm)");
        }
    }
    //owo skill
    else if(active_scene == SCENE_SKILL)
    {
        if(all_sound){
            if (!al_play_sample(skill_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &skill_bgm_id))
                game_abort("failed to play audio (bgm)");
        }
    }
    else if(active_scene == SCENE_RULE)
    {
        if(all_sound){
            if (!al_play_sample(rule_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &rule_bgm_id))
                game_abort("failed to play audio (bgm)");
        }
    }
}


void on_key_down(int keycode) {
    if (active_scene == SCENE_MENU) {
        if (keycode == ALLEGRO_KEY_ENTER){
            start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);
            if(all_sound) al_play_sample(enter_sound, 1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&enter_sound_id);
            if(select_char==1) plane.blood=100,plane.hidden=false;
            else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
            boss.blood = 500;
            for(int i=0;i<MAX_ENEMY;i++)
            enemies[i].blood=enemyblood,enemies[i].hidden=false;
            score =0 ;
            new_bullet_flag = 0;
            angle.hidden = false;
            little_flag = 1;
            game_change_scene(SCENE_START);
        }
        //owo select char
        if(keycode == ALLEGRO_KEY_S)
            game_change_scene(SCENE_SELECT);
        if(keycode == ALLEGRO_KEY_A)
            game_change_scene(SCENE_ANIMATE);
    }
    // [HACKATHON 3-10]
    // TODO: If active_scene is SCENE_SETTINGS and Backspace is pressed,
    // return to SCENE_MENU.
    else if (active_scene == SCENE_SETTINGS) {
        if (keycode == ALLEGRO_KEY_BACKSPACE){
            if(all_sound) al_play_sample(backspace_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&backspace_sound_id);
            game_change_scene(SCENE_MENU);
        }
        if (keycode == ALLEGRO_KEY_ENTER){
            start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);
            if(all_sound) al_play_sample(enter_sound, 1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&enter_sound_id);
            if(select_char==1) plane.blood=100,plane.hidden=false;
            else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
            boss.blood = 500;
            for(int i=0;i<MAX_ENEMY;i++)
            enemies[i].blood=enemyblood,enemies[i].hidden=false;
            score =0 ;
            new_bullet_flag = 0;
            angle.hidden = false;
            little_flag = 1;
            game_change_scene(SCENE_START);
        }
    }
    else if(active_scene == SCENE_SELECT)
    {
        if (keycode == ALLEGRO_KEY_ENTER){
            start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);
            if(all_sound) al_play_sample(enter_sound, 1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&enter_sound_id);
            if(select_char==1) plane.blood=100,plane.hidden=false;
            else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
            boss.blood = 500;
            for(int i=0;i<MAX_ENEMY;i++)
            enemies[i].blood=enemyblood,enemies[i].hidden=false;
            score =0 ;
            new_bullet_flag = 0;
            angle.hidden = false;
            little_flag = 1;
            game_change_scene(SCENE_START);
        }
        else if (keycode == ALLEGRO_KEY_BACKSPACE){
            if(all_sound) al_play_sample(backspace_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&backspace_sound_id);
            game_change_scene(SCENE_SETTINGS);
        }
    }
    else if(active_scene == SCENE_ANIMATE)
    {
        if (keycode == ALLEGRO_KEY_ENTER){
            start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);
            if(all_sound) al_play_sample(enter_sound, 1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&enter_sound_id);
            if(select_char==1) plane.blood=100,plane.hidden=false;
            else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
            boss.blood = 500;
            for(int i=0;i<MAX_ENEMY;i++)
            enemies[i].blood=enemyblood,enemies[i].hidden=false;
            score =0 ;
            new_bullet_flag = 0;
            angle.hidden = false;
            little_flag = 1;
            game_change_scene(SCENE_START);
        }
        else if (keycode == ALLEGRO_KEY_BACKSPACE){
            if(all_sound) al_play_sample(backspace_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&backspace_sound_id);
            game_change_scene(SCENE_MENU);
        }
    }
    else if(active_scene == SCENE_WIN){
        if(keycode == ALLEGRO_KEY_BACKSPACE)
        {
            start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);
            if(all_sound) al_play_sample(backspace_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&backspace_sound_id);
            if(select_char==1) plane.blood=100,plane.hidden=false;
            else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
                 boss.blood = 500;
                 for(int i=0;i<MAX_ENEMY;i++)
                    enemies[i].blood=enemyblood,enemies[i].hidden=false;
                 score =0 ;
                 new_bullet_flag = 0;
                 angle.hidden = false;
                 game_change_scene(SCENE_MENU);
        }
    }
    else if(active_scene == SCENE_START){
        if(keycode == ALLEGRO_KEY_BACKSPACE)
        {
                start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);
                if(all_sound) al_play_sample(backspace_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&backspace_sound_id);
                if(select_char==1) plane.blood=100,plane.hidden=false;
                 else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
                 boss.blood = 500;
                 for(int i=0;i<MAX_ENEMY;i++)
                    enemies[i].blood=enemyblood,enemies[i].hidden=false;
                 score =0 ;
                 new_bullet_flag = 0;
                 angle.hidden = false;
                 game_change_scene(SCENE_MENU);
        }
    }
    else if(active_scene == SCENE_GEME_OVER){
        if(keycode == ALLEGRO_KEY_BACKSPACE)
        {
            start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);
            if(all_sound) al_play_sample(backspace_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&backspace_sound_id);
            if(select_char==1) plane.blood=100,plane.hidden=false;
                 else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
                 boss.blood = 500;
                 for(int i=0;i<MAX_ENEMY;i++)
                    enemies[i].blood=enemyblood,enemies[i].hidden=false;
                 score =0 ;
                 new_bullet_flag = 0;
                 angle.hidden = false;
                 game_change_scene(SCENE_MENU);
        }

    }
    else if(active_scene == SCENE_SKILL){
        if (keycode == ALLEGRO_KEY_BACKSPACE){
            if(all_sound) al_play_sample(backspace_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&backspace_sound_id);
            game_change_scene(SCENE_SETTINGS);
        }
        else if(keycode == ALLEGRO_KEY_ENTER){
            if(all_sound) al_play_sample(enter_sound, 1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&enter_sound_id);
            game_change_scene(SCENE_RULE);
        }
    }
    else if(active_scene == SCENE_RULE){
        if (keycode == ALLEGRO_KEY_BACKSPACE){
            if(all_sound) al_play_sample(backspace_sound,1,0.0,1,ALLEGRO_PLAYMODE_ONCE,&backspace_sound_id);
            game_change_scene(SCENE_SETTINGS);
        }
    }
}

void on_mouse_down(int btn, int x, int y) {
    // [HACKATHON 3-8]
    // TODO: When settings clicked, switch to settings scene.
    // Uncomment and fill in the code below.
    if (active_scene == SCENE_MENU) {
        if (btn == true) {
            if (pnt_in_rect(x, y, SCREEN_W-48, 10, 38, 38))
             {
                 game_change_scene(SCENE_SETTINGS);
                 if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
             }
             //owo sound icon
             else if(pnt_in_rect(x,y,SCREEN_W-48,90,38,38)){
                all_sound = 1-all_sound;
                if(all_sound) al_play_sample(main_bgm,1,0.0,1,ALLEGRO_PLAYMODE_LOOP,&main_bgm_id);
                else al_stop_sample(&main_bgm_id);
             }
             else if(pnt_in_rect(x,y,28,10,38,38)){
                bullet_sound = 1-bullet_sound;
                if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
             }
        }
    }
    //owo select char
    else if(active_scene == SCENE_SELECT){
        if(btn == true){
            if(pnt_in_rect(mouse_x-20, mouse_y-30, 264,329, 90, 48))
            {
                select_char=1;
                if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                start_img_plane = al_load_bitmap("black_cat.png");
            }
            else if(pnt_in_rect(mouse_x-20, mouse_y-30, 639,329, 90, 48))
            {
                select_char=1;
                if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                start_img_plane = al_load_bitmap("white_cat.png");
            }
            //owo hidden role
            else if(pnt_in_rect(mouse_x-20, mouse_y-30, 264,429, 90, 48))
            {
                if(win_time>=5){
                    select_char=2;
                    if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                    img_plane2 = al_load_bitmap("strong_cat.png");
                }
            }
            else if(pnt_in_rect(mouse_x-20, mouse_y-30, 639,429, 90, 48))
            {
                if(win_time>=10){
                    select_char=2;
                    if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                    img_plane2 = al_load_bitmap("super_cat.png");
                }
            }

        }
    }
    //owo restart
    else if(active_scene == SCENE_WIN){
        if(btn == true){
            if(pnt_in_rect(mouse_x-20, mouse_y-30, 460,450, 99, 30))
             {
                 start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);
                 if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                 if(select_char==1) plane.blood=100,plane.hidden=false;
                 else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
                 boss.blood = 500;
                 for(int i=0;i<MAX_ENEMY;i++)
                    enemies[i].blood=enemyblood,enemies[i].hidden=false;
                 score =0 ;
                 new_bullet_flag = 0;
                 angle.hidden = false;
                 little_flag = 1;
                 game_change_scene(SCENE_START);
             }
        }
    }
    else if(active_scene == SCENE_GEME_OVER){
        if(btn == true){
            if(pnt_in_rect(mouse_x-20, mouse_y-30, 420,400, 99, 30))
            {
                start_img_background = load_bitmap_resized("background.jpg", SCREEN_W, SCREEN_H);
                if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                if(select_char==1) plane.blood=100,plane.hidden=false;
                 else if(select_char==2) new_plane.blood=100,new_plane.hidden=false;
                 boss.blood = 5;
                 for(int i=0;i<MAX_ENEMY;i++)
                    enemies[i].blood=enemyblood,enemies[i].hidden=false;
                 score =0 ;
                 new_bullet_flag = 0;
                 angle.hidden = false;
                 little_flag = 1;
                 game_change_scene(SCENE_START);
            }
        }
    }
    //owo setting board
    else if(active_scene == SCENE_SETTINGS){
        if(btn == true){
            if(pnt_in_rect(mouse_x-20, mouse_y-30, 358,206, 248,74)){
                if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                game_change_scene(SCENE_SELECT);
            }
            else if(pnt_in_rect(mouse_x-20, mouse_y-30, 289,350, 125,89))//simple
            {
                if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                bossswordvy = 5;
                canvx = 0+(float)rand() / RAND_MAX * 10;
                chiattackblood = 1;
                enemyblood = 50;
            }
            else if(pnt_in_rect(mouse_x-20, mouse_y-30, 530,350, 125,89))//hard
            {
                if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                bossswordvy = 10;
                canvx = 5;
                chiattackblood = 5;
                enemyblood = 100;
            }
            else if(pnt_in_rect(mouse_x-20, mouse_y-30, 420,500, 125,89))//hard
            {
                if(all_sound) al_play_sample(click_sound,2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&click_sound_id);
                game_change_scene(SCENE_SKILL);
            }
        }

    }
}


void draw_movable_object(MovableObject obj) {
    if (obj.hidden)
        return;
    al_draw_bitmap(obj.img, round(obj.x - obj.w / 2), round(obj.y - obj.h / 2), 0);
}

ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h) {
    ALLEGRO_BITMAP* loaded_bmp = al_load_bitmap(filename);
    if (!loaded_bmp)
        game_abort("failed to load image: %s", filename);
    ALLEGRO_BITMAP *resized_bmp = al_create_bitmap(w, h);
    ALLEGRO_BITMAP *prev_target = al_get_target_bitmap();

    if (!resized_bmp)
        game_abort("failed to create bitmap when creating resized image: %s", filename);
    al_set_target_bitmap(resized_bmp);
    al_draw_scaled_bitmap(loaded_bmp, 0, 0,
        al_get_bitmap_width(loaded_bmp),
        al_get_bitmap_height(loaded_bmp),
        0, 0, w, h, 0);
    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    game_log("resized image: %s", filename);

    return resized_bmp;
}

// [HACKATHON 3-3]
// TODO: Define bool pnt_in_rect(int px, int py, int x, int y, int w, int h)
// Uncomment and fill in the code below.
bool pnt_in_rect(int px, int py, int x, int y, int w, int h) {
    if(px > x-w && px < x+w && py > y-h && py < y+h)
        return true;
    return false;
}


// +=================================================================+
// | Code below is for debugging purpose, it's fine to remove it.    |
// | Deleting the code below and removing all calls to the functions |
// | doesn't affect the game.                                        |
// +=================================================================+


void game_abort(const char* format, ...) {
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
    fprintf(stderr, "error occured, exiting after 2 secs");
    // Wait 2 secs before exiting.
    al_rest(2);
    // Force exit program.
    exit(1);
}

void game_log(const char* format, ...) {
#ifdef LOG_ENABLED
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
#endif
}

void game_vlog(const char* format, va_list arg) {
#ifdef LOG_ENABLED
    static bool clear_file = true;
    vprintf(format, arg);
    printf("\n");
    // Write log to file for later debugging.
    FILE* pFile = fopen("log.txt", clear_file ? "w" : "a");
    if (pFile) {
        vfprintf(pFile, format, arg);
        fprintf(pFile, "\n");
        fclose(pFile);
    }
    clear_file = false;
#endif
}

