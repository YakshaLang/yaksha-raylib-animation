// YK:arrayutils,console,graphicutils,ini,process,raylib,whereami#
#include "yk__lib.h"
#define yy__raylib_Color Color
#define yy__raylib_color(nn__r, nn__g, nn__b, nn__a) (Color){(unsigned char)nn__r, (unsigned char)nn__g, (unsigned char)nn__b, (unsigned char)nn__a}
#define yy__raylib_Image Image
#define yy__raylib_init_window(nn__width, nn__height, nn__title) InitWindow((int)nn__width, (int)nn__height, nn__title)
#define yy__raylib_close_window() CloseWindow()
#define yy__raylib_clear_background(nn__p_color) ClearBackground(nn__p_color)
#define yy__raylib_begin_drawing() BeginDrawing()
#define yy__raylib_end_drawing() EndDrawing()
#define yy__raylib_set_target_fps(nn__fps) SetTargetFPS((int)nn__fps)
#define yy__raylib_draw_circle(nn__center_x, nn__center_y, nn__radius, nn__p_color) DrawCircle((int)nn__center_x, (int)nn__center_y, nn__radius, nn__p_color)
#define yy__raylib_load_image_from_screen() LoadImageFromScreen()
#define yy__raylib_export_image(nn__p_image, nn__file_name) ExportImage(nn__p_image, nn__file_name)
#define yy__raylib_draw_text(nn__text, nn__pos_x, nn__pos_y, nn__font_size, nn__p_color) DrawText(nn__text, (int)nn__pos_x, (int)nn__pos_y, (int)nn__font_size, nn__p_color)
#define yy__numbers_i2s(nn__a) (yk__sdsfromlonglong(nn__a))
#define yy__os_ProcessResult struct yk__process_result*
#define yy__c_CStr char*
#define yy__c_CInt int
#define yy__c_CUChar unsigned char
int32_t const  yy__SCREEN_WIDTH = INT32_C(1920);
int32_t const  yy__SCREEN_HEIGHT = INT32_C(1080);
int32_t const  yy__BALL_RADIUS = INT32_C(50);
int32_t const  yy__FPS = INT32_C(60);
int32_t const  yy__DURATION_SECONDS = INT32_C(1);
struct yy__State;
struct yy__State {
    int32_t yy__frames;
    int32_t yy__total_frames;
    yy__raylib_Image* yy__frame_caps;
};
bool yy__path_forward_slash();
bool yy__path_end_with_slash(struct yk__bstr);
yk__sds yy__path_join(struct yk__bstr, struct yk__bstr);
yy__os_ProcessResult yy__os_run(yk__sds*);
void yy__os_del_process_result(yy__os_ProcessResult);
void yy__render(struct yy__State*);
void yy__render_progress(int32_t, int32_t);
void yy__render_ffmpeg();
yk__sds yy__padded_number(int32_t, int32_t);
yk__sds yy__create_filename(int32_t);
void yy__save_frame(struct yy__State*, int32_t);
int32_t yy__main();
bool yy__path_forward_slash() 
{
    #if defined(_WIN32) || defined(_WIN64)
    bool bfwd = true;
    #else
    bool bfwd = false;
    #endif
    return bfwd;
}
bool yy__path_end_with_slash(struct yk__bstr yy__path_a) 
{
    int32_t yy__path_length = yk__bstr_len(yy__path_a);
    if (yy__path_length < INT32_C(1))
    {
        return false;
    }
    int32_t yy__path_chr = (yk__bstr_get_reference(yy__path_a)[(yy__path_length - INT32_C(1))]);
    bool yy__path_x = ((yy__path_chr == INT32_C(47)) || (yy__path_chr == INT32_C(92)));
    bool t__0 = yy__path_x;
    return t__0;
}
yk__sds yy__path_join(struct yk__bstr yy__path_a, struct yk__bstr yy__path_b) 
{
    if (yy__path_end_with_slash(yy__path_a))
    {
        yk__sds t__1 = yk__concat_bstr_bstr(yy__path_a, yy__path_b);
        yk__sds t__2 = t__1;
        return t__2;
        yk__sdsfree(t__1);
    }
yk__sds yy__path_result = yk__sdsempty();
    if (yy__path_forward_slash())
    {
        yk__sds t__3 = yk__concat_bstr_lit(yy__path_a, "\\", 1);
        yk__sds t__4 = yk__concat_sds_bstr(t__3, yy__path_b);
        yk__sdsfree(yy__path_result);
        yy__path_result = yk__sdsdup(t__4);
        yk__sdsfree(t__4);
        yk__sdsfree(t__3);
    }
    else
    {
        yk__sds t__5 = yk__concat_bstr_lit(yy__path_a, "/", 1);
        yk__sds t__6 = yk__concat_sds_bstr(t__5, yy__path_b);
        yk__sdsfree(yy__path_result);
        yy__path_result = yk__sdsdup(t__6);
        yk__sdsfree(t__6);
        yk__sdsfree(t__5);
    }
    yk__sds t__7 = yy__path_result;
    return t__7;
}
yy__os_ProcessResult yy__os_run(yk__sds* nn__args) { return yk__run(nn__args); }
void yy__os_del_process_result(yy__os_ProcessResult nn__pr) { yk__free_process_result(nn__pr); }
void yy__render(struct yy__State* yy__state) 
{
    yy__raylib_begin_drawing();
    yy__raylib_clear_background(yy__raylib_color(INT32_C(100), INT32_C(100), INT32_C(255), INT32_C(255)));
    int32_t yy__ball_x = (((yy__state->yy__frames % ((yy__SCREEN_WIDTH / INT32_C(10))))) * INT32_C(10));
    int32_t yy__ball_y = (yy__SCREEN_HEIGHT / INT32_C(2));
    yy__raylib_draw_circle(yy__ball_x, yy__ball_y, yy__BALL_RADIUS, yy__raylib_color(INT32_C(255), INT32_C(0), INT32_C(0), INT32_C(255)));
    yy__raylib_end_drawing();
    yy__raylib_Image yy__image = yy__raylib_load_image_from_screen();
    yk__arrput(yy__state->yy__frame_caps, yy__image);
    return;
}
void yy__render_progress(int32_t yy__f, int32_t yy__total) 
{
    yy__raylib_begin_drawing();
    yy__raylib_clear_background(yy__raylib_color(INT32_C(100), INT32_C(100), INT32_C(255), INT32_C(255)));
    int32_t yy__progress = (((yy__f * INT32_C(100))) / yy__total);
    yk__sds t__0 = yy__numbers_i2s(yy__progress);
    yk__sds t__1 = yk__concat_lit_sds("Exporting frames: ", 18, t__0);
    yk__sds t__2 = yk__concat_sds_lit(t__1, "%", 1);
    yk__sds yy__status = yk__sdsdup(t__2);
    yy__raylib_draw_text(((yy__c_CStr)yy__status), INT32_C(10), INT32_C(10), INT32_C(20), yy__raylib_color(INT32_C(255), INT32_C(255), INT32_C(255), INT32_C(255)));
    yy__raylib_end_drawing();
    yk__sdsfree(yy__status);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return;
}
void yy__render_ffmpeg() 
{
    yy__raylib_begin_drawing();
    yy__raylib_clear_background(yy__raylib_color(INT32_C(100), INT32_C(100), INT32_C(255), INT32_C(255)));
    yy__raylib_draw_text(((yy__c_CStr)"Rendering video..."), INT32_C(10), INT32_C(10), INT32_C(20), yy__raylib_color(INT32_C(255), INT32_C(255), INT32_C(255), INT32_C(255)));
    yy__raylib_end_drawing();
    return;
}
yk__sds yy__padded_number(int32_t yy__n, int32_t yy__pad) 
{
    yk__sds t__3 = yy__numbers_i2s(yy__n);
    yk__sds yy__ns = yk__sdsdup(t__3);
    int32_t yy__remain = (yy__pad - yk__sdslen(yy__ns));
    if (yy__remain <= INT32_C(0))
    {
        yk__sds t__4 = yy__ns;
        yk__sdsfree(t__3);
        return t__4;
    }
    yk__sds yy__result = yk__sdsnewlen("" , 0);
    while (true)
    {
        if (!(((yy__remain > INT32_C(0)))))
        {
            break;
        }
        yy__result = yk__append_sds_lit(yy__result, "0" , 1);
        yy__remain -= INT32_C(1);
    }
    yy__result = yk__append_sds_sds(yy__result, yy__ns);
    yk__sds t__5 = yy__result;
    yk__sdsfree(yy__ns);
    yk__sdsfree(t__3);
    return t__5;
}
yk__sds yy__create_filename(int32_t yy__f) 
{
    yk__sds t__6 = yy__padded_number(yy__f, INT32_C(4));
    yk__sds t__7 = yk__concat_lit_sds("frame_", 6, t__6);
    yk__sds t__8 = yk__concat_sds_lit(t__7, ".png", 4);
    yk__sds t__9 = t__8;
    yk__sdsfree(t__7);
    yk__sdsfree(t__6);
    return t__9;
}
void yy__save_frame(struct yy__State* yy__state, int32_t yy__n) 
{
    yk__sds t__10 = yy__create_filename((yy__n - INT32_C(1)));
    yk__sds t__11 = yy__path_join(yk__bstr_s("frames", 6), yk__bstr_h(t__10));
    yk__sds yy__frame_path = yk__sdsdup(t__11);
    yy__raylib_Image yy__image = yy__state->yy__frame_caps[yy__n];
    yy__raylib_export_image(yy__image, ((yy__c_CStr)yy__frame_path));
    yk__sdsfree(yy__frame_path);
    yk__sdsfree(t__11);
    yk__sdsfree(t__10);
    return;
}
int32_t yy__main() 
{
    struct yy__State* t__12 = calloc(1, sizeof(struct yy__State));
    t__12->yy__frames = (INT32_C(0));
    struct yy__State* yy__s = t__12;
    yy__raylib_init_window(yy__SCREEN_WIDTH, yy__SCREEN_HEIGHT, "Game");
    yy__raylib_set_target_fps(INT32_C(-1));
    int32_t yy__total_frames = (yy__FPS * yy__DURATION_SECONDS);
    yy__s->yy__total_frames = yy__total_frames;
    while (true)
    {
        if (!(yy__s->yy__frames <= yy__total_frames))
        {
            break;
        }
        yy__render(yy__s);
        yy__s->yy__frames += INT32_C(1);
    }
    for (int32_t yy__i = INT32_C(0);(yy__i < yy__total_frames);yy__i += INT32_C(1))
    {
        yy__save_frame(yy__s, (yy__i + INT32_C(1)));
        yy__render_progress((yy__i + INT32_C(1)), yy__total_frames);
    }
    yy__render_ffmpeg();
    yk__sds* yy__args = yk__newsdsarray(INT32_C(11), yk__sdsnewlen("ffmpeg", 6), yk__sdsnewlen("-y", 2), yk__sdsnewlen("-framerate", 10), yk__sdsnewlen("60", 2), yk__sdsnewlen("-i", 2), yk__sdsnewlen("frames/frame_%04d.png", 21), yk__sdsnewlen("-c:v", 4), yk__sdsnewlen("libx264", 7), yk__sdsnewlen("-pix_fmt", 8), yk__sdsnewlen("yuv420p", 7), yk__sdsnewlen("output.mp4", 10));
    yy__os_ProcessResult yy__result = yy__os_run(yy__args);
    yy__os_del_process_result(yy__result);
    yk__delsdsarray(yy__args);
    yy__raylib_close_window();
    free(yy__s);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif