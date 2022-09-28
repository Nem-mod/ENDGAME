#include "../inc/character.h"

t_character *mx_create_character(char *texture_path,
                                int max_hp, int attack,
                                int crit_chance, int crit_dmg,
                                int dodge_chance, int shield,
                                SDL_Window *win, SDL_Renderer *rend) {
    t_character *c = malloc(sizeof(*c));

    c->character_path = texture_path;

    SDL_QueryTexture(mx_init_texture(texture_path, win, rend), NULL, NULL,
                                    &c->character_rect.w, &c->character_rect.h);
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
        cur_dmg += from->crit_dmg;
    cur_dmg -= mx_percent_from_int(to->shield, SHIELD_DMG_ABSORB_PERCENT);
    cur_dmg = mx_int_dispersion(cur_dmg, DMG_DISP_PERCENT);

    to->current_hp -= cur_dmg; // Надо ли отнимать в функции, или лучше каждый раз вручную?
    return cur_dmg;
}
