# -*- coding: utf-8 -*-
#
# Configuration file for the Sphinx documentation builder.
#
# This file does only contain a selection of the most common options. For a
# full list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import subprocess
import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'AFF3CT'
copyright = '2018, AFF3CT team'
author = 'AFF3CT team'

# get the AFF3CT version from Git
label = subprocess.check_output(["git", "describe"]).strip().decode(encoding='UTF-8')
split_label = label.split("-")

# The short X.Y version
version = split_label[0]
# The full version, including alpha/beta/rc tags
release = label

# -- General configuration ---------------------------------------------------

# If your documentation needs a minimal Sphinx version, state it here.
#
# needs_sphinx = '1.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.mathjax',
    'sphinxcontrib.bibtex',
    'breathe'
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
#
# source_suffix = ['.rst', '.md']
source_suffix = '.rst'

# The master toctree document.
master_doc = 'index'

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = None

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []

# Figures, tables and code-blocks are automatically numbered if they have a caption
numfig = True

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = None

# -- Configure Breathe (Developer doc from Doxygen XML files) ----------------

# # Uncomment the following lines to enable the Doxygen compilation
# # Are we on a Readthedocs server ?
# read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'
# # If we are on a Readthedocs server
# if read_the_docs_build:
#     # Generate the Doxygen XML files
#     subprocess.call('cd ../../doxygen; doxygen config.txt', shell=True)
#
# breathe_projects = { "AFF3CT": "../../doxygen/xml/" }
# breathe_default_project = "AFF3CT"

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Theme options are theme-specific and customize the look and feel of a theme
# further.  For a list of options available for each theme, see the
# documentation.
# see here for description : https://sphinx-rtd-theme.readthedocs.io/en/latest/configuring.html#html-theme-options
# TODO : Why the compilation fails the first time ???? -> the second time is good.
html_theme_options = {
    'canonical_url': '', # to help search engines with duplicated versions of the doc -> TODO
    'style_external_links': False, # Add an icon next to external links.
    'display_version': True, # the version number shown at the top of the sidebar
    # Toc options
    'navigation_depth' : -1,
    'collapse_navigation': True,
    'sticky_navigation': True,
    'includehidden': False,
    'titles_only': False
}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# Custom sidebar templates, must be a dictionary that maps document names
# to template names.
#
# The default sidebars (for documents that don't match any pattern) are
# defined by theme itself.  Builtin themes are using these templates by
# default: ``['localtoc.html', 'relations.html', 'sourcelink.html',
# 'searchbox.html']``.
#
# html_sidebars = {}


html_favicon = None
html_logo    = None


# -- Options for HTMLHelp output ---------------------------------------------

# Output file base name for HTML help builder.
htmlhelp_basename = 'AFF3CTdoc'


# -- Options for LaTeX output ------------------------------------------------

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',

    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    #
    # 'preamble': '',

    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',

    'preamble': '\setcounter{tocdepth}{10}'
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
    (master_doc, 'AFF3CT.tex', 'AFF3CT Documentation',
     'AFF3CT\'s team', 'manual'),
]


# -- Options for manual page output ------------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [
    (master_doc, 'aff3ct', 'AFF3CT Documentation',
     [author], 1)
]


# -- Options for Texinfo output ----------------------------------------------

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
texinfo_documents = [
    (master_doc, 'AFF3CT', 'AFF3CT Documentation',
     author, 'AFF3CT', 'One line description of project.',
     'Miscellaneous'),
]


# -- Options for Epub output -------------------------------------------------

# Bibliographic Dublin Core info.
epub_title = project

# The unique identifier of the text. This can be a ISBN number
# or the project homepage.
#
# epub_identifier = ''

# A unique identification for the text.
#
# epub_uid = ''

# A list of files that should not be packed into the epub file.
epub_exclude_files = ['search.html']

rst_epilog = """

.. |logo_ims| image:: https://www.ims-bordeaux.fr/images/logoimsjoom.png
    :alt: logo-ims-bordeaux
    :width: 60px
    :height: 30px

.. |image_required_argument| image:: /user/simulation/parameters/images/required.png
                             :alt:  Required
                             :width:  80px
                             :height: 25px

.. |image_advanced_argument| image:: /user/simulation/parameters/images/advanced.png
                             :alt:  Advanced
                             :width:  80px
                             :height: 25px

.. |AFF3CT|   replace:: :abbr:`AFF3CT  (A Fast Forward Error Correction Toolbox!)`
.. |AMS|      replace:: :abbr:`AMS     (Approximate Min-Star)`
.. |API|      replace:: :abbr:`API     (Application Programming Interface)`
.. |ARP|      replace:: :abbr:`ARP     (Almost Regular Permutation)`
.. |ASCII|    replace:: :abbr:`ASCII   (American Standard Code for Information Interchange)`
.. |A-SCL|    replace:: :abbr:`A-SCL   (Adaptive Successive Cancellation List)`
.. |FA-SCL|   replace:: :abbr:`FA-SCL  (Fully Adaptive Successive Cancellation List)`
.. |PA-SCL|   replace:: :abbr:`PA-SCL  (Partially Adaptive Successive Cancellation List)`
.. |AVX|      replace:: :abbr:`AVX     (Advanced Vector Extensions)`
.. |AWGN|     replace:: :abbr:`AWGN    (Additive White Gaussian Noise)`
.. |AZCW|     replace:: :abbr:`AZCW    (All Zero Code Word)`
.. |AZCWs|    replace:: :abbr:`AZCWs   (All Zero Code Words)`
.. |BCH|      replace:: :abbr:`BCH     (Bose, Ray-Chaudhuri and Hocquenghem)`
.. |BCJR|     replace:: :abbr:`BCJR    (Bahl, Cocke, Jelinek and Raviv algorithm or Maximum A Posteriori (MAP))`
.. |BEC|      replace:: :abbr:`BEC     (Binary Erasure Channel)`
.. |BER|      replace:: :abbr:`BER     (Bit Error Rate)`
.. |BF|       replace:: :abbr:`BF      (Bit Flipping)`
.. |BFER|     replace:: :abbr:`BER/FER (Bit and Frame Error Rate)`
.. |BPSK|     replace:: :abbr:`BPSK    (Bit Phase-Shift Keying)`
.. |BM|       replace:: :abbr:`BM      (Berlekamp-Massey)`
.. |BP|       replace:: :abbr:`BP      (Belief Propagation)`
.. |BP-F|     replace:: :abbr:`BP-F    (Belief Propagation with Flooding scheduling)`
.. |BP-HL|    replace:: :abbr:`BP-HL   (Belief Propagation with Horizontal Layered scheduling)`
.. |BP-P|     replace:: :abbr:`BP-P    (Belief Propagation Peeling)`
.. |BP-VL|    replace:: :abbr:`BP-VL   (Belief Propagation with Vertical Layered scheduling)`
.. |BPS|      replace:: :abbr:`BPS     (Bit Per Symbol)`
.. |BSC|      replace:: :abbr:`BSC     (Binary Symmetric Channel)`
.. |CA|       replace:: :abbr:`CA      (CRC Aided)`
.. |CCSDS|    replace:: :abbr:`CCSDS   (Consultative Committee for Space Data Systems)`
.. |CDF|      replace:: :abbr:`CDF     (Cumulative Distribution Function)`
.. |CN|       replace:: :abbr:`CN      (Check Node)`
.. |CNs|      replace:: :abbr:`CNs     (Check Nodes)`
.. |codec|    replace:: :abbr:`codec   (coder/decoder)`
.. |codecs|   replace:: :abbr:`codecs  (coders/decodes)`
.. |CP|       replace:: :abbr:`CP      (Chase-Pyndiah)`
.. |CPM|      replace:: :abbr:`CPM     (Continuous Phase Modulation)`
.. |CPU|      replace:: :abbr:`CPU     (Central Process Unit)`
.. |CPUs|     replace:: :abbr:`CPUs    (Central Process Units)`
.. |CRC|      replace:: :abbr:`CRC     (Cyclic Redundancy Check)`
.. |CRCs|     replace:: :abbr:`CRCs    (Cyclic Redundancy Checks)`
.. |CSV|      replace:: :abbr:`CSV     (Comma-Separated Values)`
.. |DB|       replace:: :abbr:`DB      (Double Binary)`
.. |DE|       replace:: :abbr:`DE      (Density Evolution)`
.. |DVB-RCS1| replace:: :abbr:`DVB-RCS1(Digital Video Broadcasting - Return Channel via Satellite 1)`
.. |DVB-RCS2| replace:: :abbr:`DVB-RCS2(Digital Video Broadcasting - Return Channel via Satellite 2)`
.. |DVB-S1|   replace:: :abbr:`DVB-S1  (Digital Video Broadcasting - Satellite 1)`
.. |DVB-S2|   replace:: :abbr:`DVB-S2  (Digital Video Broadcasting - Satellite 2)`
.. |EP|       replace:: :abbr:`EP      (Event Probability)`
.. |EXIT|     replace:: :abbr:`EXIT    (EXtrinsic Information Transfer chart)`
.. |FER|      replace:: :abbr:`FER     (Frame Error Rate)`
.. |FNC|      replace:: :abbr:`FNC     (Flip aNd Check)`
.. |GA|       replace:: :abbr:`GA      (Gaussian Approximation)`
.. |GALA|     replace:: :abbr:`GALA    (Gallager A)`
.. |GPP|      replace:: :abbr:`GPP     (General Purpose Processor)`
.. |GPPs|     replace:: :abbr:`GPPs    (General Purpose Processors)`
.. |GPU|      replace:: :abbr:`GPU     (Graphics Processing Unit)`
.. |GPUs|     replace:: :abbr:`GPUs    (Graphics Processing Units)`
.. |GSL|      replace:: :abbr:`GSL     (GNU Scientific Library)`
.. |GSM|      replace:: :abbr:`GSM     (Global System for Mobile Communications)`
.. |GUI|      replace:: :abbr:`GUI     (Graphical User Interface)`
.. |IFL|      replace:: :abbr:`IFL     (Inter Frame Level)`
.. |IRA|      replace:: :abbr:`IRA     (Irregular Repeat Accumulate)`
.. |ISA|      replace:: :abbr:`ISA     (Instruction Set Architecture)`
.. |ISAs|     replace:: :abbr:`ISAs    (Instruction Set Architectures)`
.. |JSON|     replace:: :abbr:`JSON    (JavaScript Object Notation)`
.. |LDPC|     replace:: :abbr:`LDPC    (Low-Density Parity-Check)`
.. |LLRs|     replace:: :abbr:`LLRs    (Log Likelihood Ratios)`
.. |LLR|      replace:: :abbr:`LLR     (Log Likelihood Ratio)`
.. |LSPA|     replace:: :abbr:`LSPA    (Logarithmic Sum-Product Algorithm)`
.. |LTE|      replace:: :abbr:`LTE     (Long Term Evolution)`
.. |LUT|      replace:: :abbr:`LUT     (Look Up Table)`
.. |LUTs|     replace:: :abbr:`LUTs    (Look Up Tables)`
.. |MAP|      replace:: :abbr:`MAP     (Maximum A Posteriori)`
.. |MATLAB|   replace:: MATLAB
.. |MI|       replace:: :abbr:`MI      (Mutual Information)`
.. |MKL|      replace:: :abbr:`MKL     (Intel Math Kernel Library)`
.. |ML|       replace:: :abbr:`ML      (Maximum Likelihood)`
.. |modem|    replace:: :abbr:`modem   (modulator/demodulator)`
.. |modems|   replace:: :abbr:`modems  (modulators/demodulators)`
.. |MPI|      replace:: :abbr:`MPI     (Message Passing Interface)`
.. |MS|       replace:: :abbr:`MS      (Min-Sum)`
.. |MT 19937| replace:: :abbr:`MT 19937(Mersenne Twister 19937)`
.. |NEON|     replace:: :abbr:`NEON    (ARM SIMD instructions)`
.. |NMS|      replace:: :abbr:`NMS     (Normalized Min-Sum)`
.. |OMS|      replace:: :abbr:`OMS     (Offset Min-Sum)`
.. |ONMS|     replace:: :abbr:`ONMS    (Offset Normalized Min-Sum)`
.. |OOK|      replace:: :abbr:`OOK     (On-Off Keying)`
.. |OS|       replace:: :abbr:`OS      (Operating System)`
.. |OSs|      replace:: :abbr:`OSs     (Operating Systems)`
.. |PAM|      replace:: :abbr:`PAM     (Pulse-Amplitude Modulation)`
.. |PDF|      replace:: :abbr:`PDF     (Probability Density Function)`
.. |PRNG|     replace:: :abbr:`PRNG    (Pseudo Random Number Generator)`
.. |PRNGs|    replace:: :abbr:`PRNGs   (Pseudo Random Number Generators)`
.. |PSK|      replace:: :abbr:`PSK     (Phase-Shift Keying)`
.. |PyBER|    replace:: PyBER
.. |QAM|      replace:: :abbr:`QAM     (Quadrature Amplitude Modulation)`
.. |QC|       replace:: :abbr:`QC      (Quasi-Cyclic)`
.. |RA|       replace:: :abbr:`RA      (Repeat and Accumulate)`
.. |release|  replace:: """ + release + """
.. |ROP|      replace:: :abbr:`ROP     (Received Optical Power)`
.. |RSC|      replace:: :abbr:`RSC     (Recursive Systematic Convolutional)`
.. |RS|       replace:: :abbr:`RS      (Reed-Solomon)`
.. |SCAN|     replace:: :abbr:`SCAN    (Soft CANcellation)`
.. |SCL|      replace:: :abbr:`SCL     (Successive Cancellation List)`
.. |SCMA|     replace:: :abbr:`SCMA    (Sparse Code Multiple Access)`
.. |SC|       replace:: :abbr:`SC      (Successive Cancellation)`
.. |SCo|      replace:: :abbr:`SC      (Self-Corrected)`
.. |SDR|      replace:: :abbr:`SDR     (Software-Defined Radio)`
.. |SF|       replace:: :abbr:`SF      (Scaling Factor)`
.. |SFs|      replace:: :abbr:`SFs     (Scaling Factors)`
.. |SIMD|     replace:: :abbr:`SIMD    (Single Instruction Multiple Data)`
.. |SNRs|     replace:: :abbr:`SNRs    (Signal Noise Ratios)`
.. |SNR|      replace:: :abbr:`SNR     (Signal Noise Ratio)`
.. |SPC|      replace:: :abbr:`SPC     (Single Parity Check)`
.. |SPA|      replace:: :abbr:`SPA     (Sum-Product Algorithm)`
.. |SSE|      replace:: :abbr:`SSE     (Streaming SIMD Extensions)`
.. |STD|      replace:: :abbr:`STD     (Standard)`
.. |TPC|      replace:: :abbr:`TPC     (Turbo Product Code)`
.. |TV|       replace:: :abbr:`TV      (Tal & Vardy)`
.. |version|  replace:: """ + version + """
.. |VN|       replace:: :abbr:`VN      (Variable Node)`
.. |VNs|      replace:: :abbr:`VNs     (Variable Nodes)`
.. |WBF|      replace:: :abbr:`WBF     (Weighted Bit Flipping)`

"""

# -- Extension configuration -------------------------------------------------
