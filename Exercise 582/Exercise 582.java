package diophant;

import utils.Farey;

import java.util.HashSet;
import java.util.Set;

import static java.lang.Math.log;
import static java.lang.Math.sqrt;

public class E582NearlyIsosceles120DegreeTriangles {

    static double cMax = 1e100;

    static Set<Farey.Pair> solvePrimitive(int d) {
        int d2 = d * d;
        Set<Farey.Pair> r = new HashSet<>();
        for (int y = 0; y < d / sqrt(6); y++) {
            final int x2 = 3 * y * y + d2;
            int x = (int) sqrt(x2);
            if (x * x == x2) {
                Farey.Pair p = new Farey.Pair(x, y);
                r.add(makeAdmissible(p, d));
                p = new Farey.Pair(x, -y);
                r.add(makeAdmissible(p, d));
            }
        }
        return r;
    }

    static Farey.Pair makeAdmissible(Farey.Pair p, int d) {
        while (p.getA() % 2 == 1 || p.getB() <= d)
            p = next(p);
        return p;
    }

    static int count(Farey.Pair p, int d) {
        double log = (d % 2 == 0) ? log(2 + sqrt(3)) : log(7 + 4 * sqrt(3));
        return (int) ((log(4 * cMax) - log(p.getA() + sqrt(3) * p.getB())) / log) + 1;
    }

    static Farey.Pair next(Farey.Pair p) {
        return new Farey.Pair(2 * p.getA() + 3 * p.getB(), p.getA() + 2 * p.getB());
    }

    static int countSmall(Farey.Pair p, int d) {
        int count = 0;
        while (p.getA() <= 2 * cMax) {
            if (p.getA() % 2 == 0 && d < p.getB()) {
                count++;
            }
            p = next(p);
        }
        return count;
    }

    static long count(int d) {
        long count = 0;
        for (Farey.Pair p : solvePrimitive(d)) {
            count += (cMax > 1e8) ? count(p, d) : countSmall(p, d);
        }
        return count;
    }

    public static void main(String[] args) {
        long count = 0;
        for (int d = 1; d <= 100; d++)
            count += count(d);
        System.out.println(count);
    }
}