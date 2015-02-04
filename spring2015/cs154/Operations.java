import java.util.*;
import java.util.function.*;

public class Operations {
    public static <T> Set<T> intersect(Set<T> a, Set<T> b) {
        Set<T> c = new HashSet<T>();
        for (T ele : a) {
            if (b.contains(ele)) {
                c.add(ele);
            }
        }
        return c;
    }

    public static <T> Set<T> union(Set<T> a, Set<T> b) {
        Set<T> c = new HashSet<T>();
        for (T ele : a) {
            c.add(ele);
        }
        for (T ele : b) {
            c.add(ele);
        }
        return c;
    }

    public static <T> Set<T> diff(Set<T> a, Set<T> b) {
        Set<T> c = new HashSet<T>();
        for (T ele : a) {
            if (!b.contains(ele)) {
                c.add(ele);
            }
        }
        return c;

    }

    public static <T> boolean subset(Set<T> a, Set<T> b) {
        for (T ele : a) {
            if (!b.contains(ele)) {
                return false;
            }
        }
        return true;
    }

    public static <T> Set<T> filter(Set<T> a, Predicate<T> f) {
        Set<T> b = new HashSet<T>();
        for (T ele : a) {
            if (f.test(ele)) {
                b.add(ele);
            }
        }
        return b;
    }

    public static <T> Set<T> map(Set<T> a, UnaryOperator<T> f) {
        Set<T> b = new HashSet<T>();
        for (T ele : a) {
            b.add(f.apply(ele));
        }
        return b;
    }

    public static <T> Set<Set<T>> power(Set<T> a) {
        Set<Set<T>> b = new HashSet<Set<T>>();
        if (a.isEmpty()) {
            b.add(new HashSet<T>());
            return b;
        }

        List<T> list = new ArrayList<T>(a);
        T head = list.get(0);
        Set<T> rest = new HashSet<T>(list.subList(1, list.size()));
        for (Set<T> set : power(rest)) {
            Set<T> newSet = new HashSet<T>();
            newSet.add(head);
            newSet.addAll(set);
            b.add(newSet);
            b.add(set);
        }
        return b;
    }

    public static String unicode(int i) {
        return "";
    }
}
