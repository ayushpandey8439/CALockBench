package main.struct;

import java.util.List;
import java.util.Set;

public class designObject {
    long ID;
    long buildDate;
    long m_pre_number;
    long m_post_number;
    boolean hasLabel;
    List<Integer> pathLabel;
    Set<Integer> criticalAncestors;
    int labellingId;

    public designObject(long id, int d){
        ID=id;
        buildDate = d;
        this.m_pre_number=0;
        this.m_post_number=0;
        this.hasLabel = false;
    }

    public void setPathLabel(List<Integer> label){
        this.hasLabel = true;
        this.pathLabel = label;
        this.criticalAncestors.clear();
        this.criticalAncestors.addAll(label);
        this.labellingId = label.get(label.size()-1);
    }
}
