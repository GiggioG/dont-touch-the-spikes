#include "Spikes.h"
#include "Presenter.h"
#include "ConfigManager.h"
#include "Engine.h"
#include "TextureManager.h"

extern ConfigManager* cfgm;

Spikes::Spikes() {}
Spikes::~Spikes() {}


int randInInterval(int from, int to) {
    if (to < from) { swap(from, to); }
    int diff = to - from + 1;
    return from + (rand()%diff);
}

int spikeWidth, spikeInterval, gapWidthMin, gapWidthMax, gapBeginMin;
int bonbonDiam, bonbonRad;

void Spikes::init(int beginX) {
    spikeWidth = cfgm->cfg["SPIKE_WIDTH"].i;
    spikeInterval = cfgm->cfg["SPIKE_INTERVAL"].i;
    gapWidthMin = cfgm->cfg["GAP_WIDTH_MIN"].i;
    gapWidthMax = cfgm->cfg["GAP_WIDTH_MAX"].i;
    gapBeginMin = cfgm->cfg["GAP_BEGIN_MIN"].i;

    bonbonDiam = cfgm->cfg["BONBON_DIAMETER"].i;
    bonbonRad = bonbonDiam / 2;

    topLongRect.w = Presenter::m_SCREEN_WIDTH;
    topLongRect.h = spikeWidth;
    topLongRect.x = 0;
    topLongRect.y = 0;

    bottomLongRect.w = Presenter::m_SCREEN_WIDTH;
    bottomLongRect.h = spikeWidth;
    bottomLongRect.x = 0;
    bottomLongRect.y = Presenter::m_SCREEN_HEIGHT - bottomLongRect.h;

    makeSpikes(beginX, true);
}

int calcMid(pair<SDL_Rect, SDL_Rect> sp) {
    return (sp.first.h + sp.second.y) / 2;
}

void Spikes::makeSpikes(int beginX, bool right){
    middle.clear();
    int inc = spikeInterval * (right ? 1 : -1);
    for (int x = beginX+inc; x >= 0 && x + spikeWidth < Presenter::m_SCREEN_WIDTH; x += inc) {
        int gap = randInInterval(gapWidthMin, gapWidthMax);
        int gapStart = randInInterval(gapBeginMin, Presenter::m_SCREEN_HEIGHT - gapBeginMin - gap);
        SDL_Rect top;
        SDL_Rect bottom;

        top.x = x;
        bottom.x = x;
        top.w = spikeWidth;
        bottom.w = spikeWidth;

        top.y = 0;
        bottom.y = gapStart + gap;
        top.h = gapStart;
        bottom.h = Presenter::m_SCREEN_HEIGHT - bottom.y;

        middle.push_back({ top, bottom });
    }
    
    int idx = randInInterval(0, middle.size()-1);
    if (idx >= 0 && idx < middle.size()) {
        bonbon.x = middle[idx].first.x + spikeWidth / 2;
        bonbon.y = calcMid(middle[idx]);
        bonbonActive = true;
    } else {
        bonbonActive = false;
    }
}

void Spikes::draw() {
    Drawable topLong;
    topLong.texture = TextureManager::longSpikes_texture;
    topLong.rect = topLongRect;
    topLong.flip = SDL_FLIP_VERTICAL;
    drawObject(topLong);

    Drawable bottomLong;
    bottomLong.texture = TextureManager::longSpikes_texture;
    bottomLong.rect = bottomLongRect;
    drawObject(bottomLong);

    for(int i = 0; i < middle.size(); i++){
        Drawable top, bottom;
        top.rect = middle[i].first;
        bottom.rect = middle[i].second;

        top.texture = TextureManager::spike_texture;
        bottom.texture = TextureManager::spike_texture;

        top.flip = SDL_FLIP_VERTICAL;

        drawObject(top);
        drawObject(bottom);
    }

    if (bonbonActive) {
        Drawable bon;
        bon.rect.x = bonbon.x - bonbonRad;
        bon.rect.y = bonbon.y - bonbonRad;
        bon.rect.w = bonbonDiam;
        bon.rect.h = bonbonDiam;
        bon.texture = TextureManager::bonbon_texture;
        drawObject(bon);
    }
}

void Spikes::destruct() {

}

void Spikes::remakeBonbonIfNess(const Pile& p){
    if (!bonbonActive) { return; }
    bool needed = false;
    bool right = (p.vel.x > 0);
    if (right) {
        if (p.pos.x - bonbon.x > p.radius + bonbonRad) { needed = true; }
    }else {
        if (bonbon.x - p.pos.x > p.radius + bonbonRad) { needed = true; }
    }
    if (!needed) { return; }
    vector<int> cand;
    for (int i = 0; i < middle.size(); i++) {
        int mx = middle[i].first.x + spikeWidth / 2;
        if ((mx > p.pos.x && right) || (mx < p.pos.x && !right)) {
            cand.push_back(i);
        }
    }
    int idx = randInInterval(0, cand.size() - 1);
    if (idx >= 0 && idx < cand.size()) {
        bonbon.x = middle[cand[idx]].first.x + spikeWidth / 2;
        bonbon.y = calcMid(middle[cand[idx]]);
        bonbonActive = true;
    }
    else {
        bonbonActive = false;
    }
}

bool Spikes::collide(Pile& p){
    if (p.collide(topLongRect)) { return true; }
    if (p.collide(bottomLongRect)) { return true; }
    for (int i = 0; i < middle.size(); i++) {
        if (p.collide(middle[i].first) || p.collide(middle[i].second)) {
            return true;
        }
    }
    return false;
}

bool Spikes::bonbonCollide(Pile& p) {
    if (!bonbonActive) { return false; }
    int dx = bonbon.x - p.pos.x;
    int dy = bonbon.y - p.pos.y;

    int dist2 = dx * dx + dy * dy;
    int maxTouch2 = (bonbonRad + p.radius) * (bonbonRad + p.radius);

    return (dist2 <= maxTouch2);
}
