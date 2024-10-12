#include "riseset_utils.cpp"

RiseSetArray riseset_union(const RiseSetArray& a, const RiseSetArray& b) {
    RiseSetArray c;
    if (a.size() == 0) {
        c = b;
        return c;
    }
    else if (b.size() == 0) {
        c = a;
        return c;
    }

    // TODO: Actual union

    return c;
}

RiseSetArray riseset_intersection(const RiseSetArray& a, const RiseSetArray& b) {
    RiseSetArray c;
    if (a.size() == 0) {
        c = b;
        return c;
    }
    else if (b.size() == 0) {
        c = a;
        return c;
    }

    // TODO: Actual intersection

    return c;
}