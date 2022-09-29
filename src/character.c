#include "../inc/character.h"

t_character *mx_create_character(char *texture_path,
                                int max_hp, int attack,
                                int crit_chance, int crit_dmg,
                                int dodge_chance, int shield,
                                SDL_Window *win, SDL_Renderer *rend) {
    t_character *c = malloc(sizeof(*c));

    c->character_path = texture_path;

    SDL_QueryTexture(mx_init_texture(texture_path, win, rend), NULL, NULL,
                                    &c->character_rect.w, &c->character_rect.h); // Тут берется размер спрайта. Нужно будет подгонять размер позже. Нужна функция для этого
    c->character_texture = mx_init_texture(texture_path, win, rend);

    mx_set_character(c, max_hp, attack, crit_chance, crit_dmg, dodge_chance, shield);

    return c;
}

void mx_set_character(t_character *c,
                    int max_hp, int attack,
                    int crit_chance, int crit_dmg,
                    int dodge_chance, int shield) {
    c->max_hp = max_hp;
    c->current_hp = max_hp;
    c->attack = attack;
    c->crit_chance = crit_chance;
    c->crit_dmg = crit_dmg;
    c->dodge_chance = dodge_chance;
    c->shield = shield;
}
void mx_set_enemy(t_character *c) {
    c->max_hp = rand() % 80 + 50;
    c->current_hp = c->max_hp;
    c->attack = 20;
    c->crit_chance = rand() % 10;
    c->crit_dmg = rand() % 10;
    c->dodge_chance = rand() % 10;
    c->shield = 0;
}
void mx_clear_character(t_character *character) {
    SDL_DestroyTexture(character->character_texture);
    free(character);
    character = NULL;
}

int mx_calculate_attack(t_character *from, t_character *to) {
    int cur_dmg = from->attack;

    if (mx_chance(to->dodge_chance))
        return -1; // -1 означает dodge. Надо придумать чет с этим и мб переделать т.к -1 не понять нихуя
    if (mx_chance(from->crit_chance))
        cur_dmg += mx_percent_from_int(from->attack, from->crit_dmg);

    cur_dmg = mx_int_dispersion(cur_dmg, DMG_DISP_PERCENT);

    cur_dmg -= to->shield;
    to->shield = -cur_dmg;

    if (cur_dmg < 0)
        cur_dmg = 0;
    if (to->shield < 0)
        to->shield = 0;

    to->current_hp -= cur_dmg; // Надо ли отнимать в функции, или лучше каждый раз вручную?
    return cur_dmg;
}

void mx_render_character(t_character *character, SDL_Renderer *rend, SDL_Rect rect) {
    SDL_RenderCopy(rend, character->character_texture, NULL, &rect);
    mx_render_bar(character->healthbar, rend);
    mx_render_bar(character->shieldbar, rend);
    // SDL_RenderCopy(rend, character->healthbar->bar_texture, NULL, &character->healthbar->bar_rect);
}
