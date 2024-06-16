package Prim_Folder;

import Graph.Arch;

import java.util.Comparator;

public class ArchFloatComparator implements Comparator<Arch<String, Float>> {
    @Override
    public int compare(Arch<String, Float> r1, Arch<String, Float> r2) {
        return Float.compare(r1.getLabel(), r2.getLabel());
    }
}