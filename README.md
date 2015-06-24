# HipSTR
**H**aplotype-based **i**mputation, **p**hasing and genotyping of **STR**s

#### Author: Thomas Willems <twillems@mit.edu>
#### License: GNU v2

## Introduction
Short tandem repeats [(STRs)](http://en.wikipedia.org/wiki/Microsatellite) are highly repetitive genomic sequences comprised of repeated copies of an underlying motif. Prevalent in most organisms' genomes, STRs are of particular interest because they mutate much more rapidly than most other genomic elements. As a result, they're extremely informative for genomic identification, ancestry inference and genealogy.

Despite their utility, STRs are particularly difficult to genotype . The repetitive sequence responsible for their high mutability also results in frequent alignment errors that can complicate and bias downstream analyses. In addition, PCR stutter errors often result in reads that contain additional or fewer repeat copies than the true underlying genotype. 

**HipSTR** was specifically developed to deal with these errors in the hopes of obtaining more robust STR genotypes. In particular, it accomplishes this by:

1. Learning locus-specific PCR stutter models using an [EM algorithm] (http://en.wikipedia.org/wiki/Expectation%E2%80%93maximization_algorithm)
2. Mining candidate STR alleles from population-scale sequencing data
2. Utilizing phased SNP haplotypes to genotype, phase and/or impute STRs
3. Employing a specialized hidden Markov model to align reads to candidate sequences while accounting for stutter



## Installation
HipSTR requires a standard c++ compiler as well as Java version 1.7 or later.
To obtain HipSTR and all of its associated  submodules, use:

    % git clone --recursive https://github.com/tfwillems/HipSTR.git

To build, use Make:

    % cd HipSTR
    % make

On Mac, before running Make, change the line in *vcflib/smithwaterman/Makefile* from

    % LDFLAGS=-Wl,-s
to

    % LDFLAGS=-Wl

## Quick Start
To run HipSTR in its most common mode, run it on **all samples concurrently** using the syntax:
```
./HipSTR --bams          sample1.bam,sample2.bam,sample3.bam 
         --indexes       sample1.bam.bai,sample2.bam.bai,sample3.bam.bai
         --rgs           SAMPLE1,SAMPLE2,SAMPLE3
         --fasta         /data/hg19_by_chrom/
         --regions       str_regions.bed
         --seq-genotyper
         --stutter-out   stutter_models.txt
         --str-vcf       str_calls.vcf.gz
```
* --bam :  a comma-separated list of  [BAM](https://samtools.github.io/hts-specs/SAMv1.pdf) files for each sample of interest generated by any indel-sensitive aligner
* --indexes : a comma-separated list of index files for each BAM file generated using [*samtools*](http://www.htslib.org/)
* --rgs : the sample associated with each BAM. If your BAMs contain multiple samples, see below
* --regions: a [BED](https://genome.ucsc.edu/FAQ/FAQformat.html#format1) file containing the coordinates for each STR region of interest
* --fasta: the directory containing [FASTA files] (https://en.wikipedia.org/wiki/FASTA_format) for each chromosome in the BED file. In the above usage example, if *str_regions.bed* contains chr1, chr2, and chr10, the corresponding files would be */data/chr1.fa*, */data/chr2.fa* and */data/chr10.fa*

For each region in */data/str_regions.bed*, **HipSTR** will:

1. Learn locus-specific stutter models and output them to *stutter_models.txt*
2. Use the stutter model and haplotype-based alignment algorithm to genotype each individual
3. Output the resulting STR genotypes to *str_calls.vcf.gz*, a [bgzipped] (http://www.htslib.org/doc/tabix.html) [VCF] (http://samtools.github.io/hts-specs/VCFv4.2.pdf) file


## In-depth usage 
### 1. De novo STR calling
In this mode, **HipSTR** will identify candidate STR alleles strongly supported by any of the samples. This approach works best if the analysis is restricted to high coverage samples or if the analysis involves population-scale (~1000 samples) low-coverage sequencing data.

```
./HipSTR --bams    sample1.bam,sample2.bam,sample3.bam 
         --indexes sample1.bam.bai,sample2.bam.bai,sample3.bam.bai
         --fasta   /data/hg19_by_chrom/
         --regions /data/str_regions.bed
         --seq-genotyper
         --str-vcf str_calls.vcf.gz
```

### 2. STR calling using a reference panel of STRs
If you're restricted to analyzing only a handful of low-coverage samples, it 
```
./HipSTR --bams    sample1.bam,sample2.bam,sample3.bam 
         --indexes sample1.bam.bai,sample2.bam.bai,sample3.bam.bai
         --fasta   /data/hg19_by_chrom/
         --regions /data/str_regions.bed
         --seq-genotyper
         --str-vcf str_calls.vcf.gz
         --ref-vcf ref_strs.vcf.gz
```


### STR imputation


## Additional Usage Options

## Alignment Visualization
