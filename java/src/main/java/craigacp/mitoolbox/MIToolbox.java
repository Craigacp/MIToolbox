/*
** MIToolbox.java
**
** Initial Version - 14/01/2018
** Author - Adam Pocock
** 
** Part of MIToolbox
**
** Please check www.github.com/Craigacp/MIToolbox for updates.
** 
**  Copyright 2010-2018 Adam Pocock, The University Of Manchester
**  www.cs.manchester.ac.uk
**
**  This file is part of MIToolbox, licensed under the 3-clause BSD license.
*/
package craigacp.mitoolbox;

import java.util.HashMap;
import java.util.List;

/**
 * The accessor class for MIToolbox functions.
 * 
 * @author craigacp
 */
public abstract class MIToolbox {

    private MIToolbox() {}

    static {
        System.loadLibrary("mitoolbox-java");
    }

    private static native double checkedhx(int[] x);

    public static double hx(int[] x) {
        return checkedhx(x);
    }

    public static <T> double hx(List<T> x) {
        int[] discX = convertList(x);
        return hx(discX);
    }

    private static native double checkedhxcondy(int[] x, int[] y);

    public static double hxcondy(int[] x, int[] y) {
	validateInputs(x,y);
	return checkedhxcondy(x,y);
    }

    public static <T,U> double hxcondy(List<T> x, List<U> y) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        return hxcondy(discX,discY);
    }
    
    private static native double checkedhxy(int[] x, int[] y);

    public static double hxy(int[] x, int[] y) {
	validateInputs(x,y);
	return checkedhxy(x,y);
    }

    public static <T,U> double hxy(List<T> x, List<U> y) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        return hxy(discX,discY);
    }
    
    private static native double checkedmi(int[] x, int[] y);

    public static double mi(int[] x, int[] y) {
	validateInputs(x,y);
	return checkedmi(x,y);
    }

    public static <T,U> double mi(List<T> x, List<U> y) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        return mi(discX,discY);
    }
    
    private static native double checkedcmi(int[] x, int[] y, int[] z);

    public static double cmi(int[] x, int[] y, int[] z) {
	validateInputs(x,y,z);
	return checkedcmi(x,y,z);
    }

    public static <T,U,V> double cmi(List<T> x, List<U> y, List<V> z) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        int[] discZ = convertList(z);
        return cmi(discX,discY,discZ);
    }

    private static native double checkedRenyiEntropy(double alpha, int[] x);

    public static double renyiEntropy(double alpha, int[] x) {
        return checkedRenyiEntropy(alpha,x);
    }

    public static <T> double renyiEntropy(double alpha, List<T> x) {
        int[] discX = convertList(x);
        return renyiEntropy(alpha,discX);
    }

    private static native double checkedRenyiJointEntropy(double alpha, int[] x, int[] y);

    public static double renyiJointEntropy(double alpha, int[] x, int[] y) {
	validateInputs(x,y);
	return checkedRenyiJointEntropy(alpha,x,y);
    }

    public static <T,U> double renyiJointEntropy(double alpha, List<T> x, List<U> y) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        return renyiJointEntropy(alpha,discX,discY);
    }
    
    private static native double checkedRenyiMI(double alpha, int[] x, int[] y);

    public static double renyiMI(double alpha, int[] x, int[] y) {
	validateInputs(x,y);
	return checkedRenyiMI(alpha,x,y);
    }

    public static <T,U> double renyiMI(double alpha, List<T> x, List<U> y) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        return renyiMI(alpha,discX,discY);
    }

    private static native double checkedwhx(int[] x, double[] weights);

    public static double whx(int[] x, double[] weights) {
        validateInputs(x,weights);
        return checkedwhx(x,weights);
    }

    public static <T> double whx(List<T> x, double[] weights) {
        int[] discX = convertList(x);
        return whx(discX,weights);
    }

    private static native double checkedwhxcondy(int[] x, int[] y, double[] weights);
    
    public static double whxcondy(int[] x, int[] y, double[] weights) {
        validateInputs(x,y,weights);
        return checkedwhxcondy(x,y,weights);
    }

    public static <T,U> double whxcondy(List<T> x, List<U> y, double[] weights) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        return whxcondy(discX,discY,weights);
    }
    
    private static native double checkedwhxy(int[] x, int[] y, double[] weights);
    
    public static double whxy(int[] x, int[] y, double[] weights) {
        validateInputs(x,y,weights);
        return checkedwhxy(x,y,weights);
    }

    public static <T,U> double whxy(List<T> x, List<U> y, double[] weights) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        return whxy(discX,discY,weights);
    }
    
    private static native double checkedwmi(int[] x, int[] y, double[] weights);
    
    public static double wmi(int[] x, int[] y, double[] weights) {
        validateInputs(x,y,weights);
        return checkedwmi(x,y,weights);
    }

    public static <T,U> double wmi(List<T> x, List<U> y, double[] weights) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        return wmi(discX,discY,weights);
    }
    
    private static native double checkedwcmi(int[] x, int[] y, int[] z, double[] weights);
    
    public static double wcmi(int[] x, int[] y, int[] z, double[] weights) {
        validateInputs(x,y,z,weights);
        return checkedwcmi(x,y,z,weights);
    }

    public static <T,U,V> double wcmi(List<T> x, List<U> y, List<V> z, double[] weights) {
        int[] discX = convertList(x);
        int[] discY = convertList(y);
        int[] discZ = convertList(z);
        return wcmi(discX,discY,discZ,weights);
    }
    
    public static <T> int[] convertList(List<T> input) {
        int[] output = new int[input.size()];
        int counter = 0;

        HashMap<T, Integer> idMapping = new HashMap<>();
        int idxCounter = 0;

        for (T element : input) {
            Integer idx = idMapping.getOrDefault(element, -1);
            if (idx == -1) {
                idx = idxCounter;
                idMapping.put(element, idx);
                idxCounter++;
            }
            output[counter] = idx;
            counter++;
        }

        return output;
    }

    private static void validateInputs(int[] x, int[] y) {
        if (x.length != y.length) {
            throw new IllegalArgumentException("X and Y are not the same length, x.length = " + x.length + ", y.length = " + y.length);
        }	
    }

    private static void validateInputs(int[] x, int[] y, int[] z) {
        if ((x.length != y.length) || (x.length != z.length)) {
            throw new IllegalArgumentException("X, Y and Z are not the same length, x.length = " + x.length + ", y.length = " + y.length + ", z.length " + z.length);
        }	
    }

    private static void validateInputs(int[] x, double[] w) {
        if (x.length != w.length) {
            throw new IllegalArgumentException("X and weights are not the same length, x.length = " + x.length + ", weights.length " + w.length);
        }
    }

    private static void validateInputs(int[] x, int[] y, double[] w) {
        if ((x.length != y.length) || (x.length != w.length)) {
            throw new IllegalArgumentException("X, Y and weights are not the same length, x.length = " + x.length + ", y.length = " + y.length + ", weights.length " + w.length);
        }
    }

    private static void validateInputs(int[] x, int[] y, int[] z, double[] w) {
        if ((x.length != y.length) || (x.length != z.length) || (x.length != w.length)) {
            throw new IllegalArgumentException("X, Y, Z and weights are not the same length, x.length = " + x.length + ", y.length = " + y.length + ", z.length = " + z.length + ", weights.length " + w.length);
        }
    }
}
