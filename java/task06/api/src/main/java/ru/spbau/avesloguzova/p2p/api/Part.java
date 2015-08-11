package ru.spbau.avesloguzova.p2p.api;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by av on 6/23/15.
 */
public class Part {
    private final int id;
    private final List<String> seeds;

    public Part(int id) {
        this.id = id;
        this.seeds = new ArrayList<>();
    }
    public Part(int id, String firstSeed){
        this.id = id;
        seeds= new ArrayList<>();
        seeds.add(firstSeed);
    }
    public int getId() {
        return id;
    }
    synchronized public void addSeed(String seed){
        seeds.add(seed);
    }


}
